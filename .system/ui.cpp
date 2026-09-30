#include "ui.hpp"

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/ioctl.h>

namespace ui {

static int cached_border = 0;
static int cached_margin = -1;

static int term_columns(void)
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 20)
        return (w.ws_col);
    const char *c = std::getenv("COLUMNS");
    if (c != NULL)
    {
        int n = atoi(c);
        if (n > 20)
            return (n);
    }
    return (80);
}

int border_width(void)
{
    if (cached_border == 0)
    {
        int t = term_columns();
        // keep one column free so the right border never wraps
        cached_border = std::min(t - 1, 84);
        if (cached_border < 40)
            cached_border = 40;
    }
    return (cached_border);
}

int text_width(void)
{
    return (border_width() - 4);
}

static int left_margin(void)
{
    if (cached_margin < 0)
    {
        int t = term_columns();
        int b = border_width();
        cached_margin = (t - b) / 2;
        if (cached_margin < 0)
            cached_margin = 0;
    }
    return (cached_margin);
}

static std::string margin_str(void)
{
    return (std::string(left_margin(), ' '));
}

// Decode one UTF-8 codepoint starting at s[i]; advances i past it.
static unsigned int decode_utf8(const std::string &s, size_t &i)
{
    unsigned char c = (unsigned char)s[i];
    unsigned int cp = c;
    int extra = 0;
    if (c >= 0xF0)
    {
        cp = c & 0x07;
        extra = 3;
    }
    else if (c >= 0xE0)
    {
        cp = c & 0x0F;
        extra = 2;
    }
    else if (c >= 0xC0)
    {
        cp = c & 0x1F;
        extra = 1;
    }
    i++;
    while (extra-- > 0 && i < s.size() && ((unsigned char)s[i] & 0xC0) == 0x80)
        cp = (cp << 6) | ((unsigned char)s[i++] & 0x3F);
    return (cp);
}

// Columns taken by a codepoint in a typical terminal.
static int codepoint_width(unsigned int cp)
{
    // zero width: variation selectors, zero width joiner / space
    if ((cp >= 0xFE00 && cp <= 0xFE0F) || cp == 0x200D || cp == 0x200B)
        return (0);
    // wide: emoji and east-asian wide ranges
    if ((cp >= 0x1100 && cp <= 0x115F) || cp == 0x231A || cp == 0x231B
        || (cp >= 0x23E9 && cp <= 0x23EC) || cp == 0x23F0 || cp == 0x23F3
        || cp == 0x2614 || cp == 0x2615 || cp == 0x26A1 || cp == 0x26AA
        || cp == 0x26AB || cp == 0x26BD || cp == 0x26BE || cp == 0x26C4
        || cp == 0x26C5 || cp == 0x26D4 || cp == 0x26F5 || cp == 0x26FA
        || cp == 0x26FD || cp == 0x2705 || cp == 0x270A || cp == 0x270B
        || cp == 0x2728 || cp == 0x274C || cp == 0x274E
        || (cp >= 0x2753 && cp <= 0x2755) || cp == 0x2757
        || (cp >= 0x2795 && cp <= 0x2797) || cp == 0x27B0 || cp == 0x27BF
        || cp == 0x2B1B || cp == 0x2B1C || cp == 0x2B50 || cp == 0x2B55
        || (cp >= 0x2E80 && cp <= 0xA4CF) || (cp >= 0xAC00 && cp <= 0xD7A3)
        || (cp >= 0xF900 && cp <= 0xFAFF) || (cp >= 0xFF00 && cp <= 0xFF60)
        || (cp >= 0xFFE0 && cp <= 0xFFE6) || (cp >= 0x1F300 && cp <= 0x1F64F)
        || (cp >= 0x1F680 && cp <= 0x1F6FF) || (cp >= 0x1F900 && cp <= 0x1FAFF))
        return (2);
    return (1);
}

// Length of the ANSI escape sequence starting at s[i] (0 if none).
static size_t escape_len(const std::string &s, size_t i)
{
    if (s[i] != '\033' || i + 1 >= s.size() || s[i + 1] != '[')
        return (0);
    size_t j = i + 2;
    while (j < s.size() && !(s[j] >= '@' && s[j] <= '~'))
        j++;
    return (j < s.size() ? j - i + 1 : s.size() - i);
}

int display_width(const std::string &s)
{
    int w = 0;
    size_t i = 0;
    while (i < s.size())
    {
        size_t esc = escape_len(s, i);
        if (esc)
        {
            i += esc;
            continue;
        }
        w += codepoint_width(decode_utf8(s, i));
    }
    return (w);
}

std::string pad(const std::string &s, int cw)
{
    if (cw < 0)
        cw = text_width();
    int w = display_width(s);
    if (w >= cw)
        return (s);
    return (s + std::string(cw - w, ' '));
}

std::string truncate(const std::string &s, int max_w)
{
    if (max_w <= 0)
        return ("");
    if (display_width(s) <= max_w)
        return (s);
    int target = max_w - 3;
    if (target < 0)
        target = 0;
    std::string result;
    int rw = 0;
    size_t i = 0;
    while (i < s.size())
    {
        size_t esc = escape_len(s, i);
        if (esc)
        {
            result += s.substr(i, esc);
            i += esc;
            continue;
        }
        size_t start = i;
        int cw = codepoint_width(decode_utf8(s, i));
        if (rw + cw > target)
            break;
        result += s.substr(start, i - start);
        rw += cw;
    }
    return (result + U_RESET + "...");
}

// Number of bytes of s that fit in `cols` columns (escapes included).
static size_t prefix_bytes(const std::string &s, int cols)
{
    int w = 0;
    size_t i = 0;
    while (i < s.size())
    {
        size_t esc = escape_len(s, i);
        if (esc)
        {
            i += esc;
            continue;
        }
        size_t start = i;
        int cw = codepoint_width(decode_utf8(s, i));
        if (w + cw > cols)
            return (start);
        w += cw;
    }
    return (i);
}

// Split text into lines no wider than `width`, breaking on spaces.
// Colors active at a break are re-applied on the next line, and
// continuation lines keep the original leading indentation.
std::vector<std::string> wrap(const std::string &text, int width)
{
    std::vector<std::string> out;
    if (width <= 0 || display_width(text) <= width)
    {
        out.push_back(text);
        return (out);
    }

    // leading spaces (escape sequences before/among them are kept)
    size_t start_i = 0;
    size_t lead = 0;
    std::string active; // SGR sequences since the last reset
    while (start_i < text.size())
    {
        size_t esc = escape_len(text, start_i);
        if (esc)
        {
            std::string seq = text.substr(start_i, esc);
            if (seq == "\033[0m" || seq == "\033[m")
                active.clear();
            else if (seq.back() == 'm')
                active += seq;
            start_i += esc;
        }
        else if (text[start_i] == ' ')
        {
            start_i++;
            lead++;
        }
        else
            break;
    }
    std::string indent(std::min<size_t>(lead, (size_t)width / 2), ' ');

    std::string cur = text.substr(0, start_i);
    int cur_w = (int)lead;
    std::string word;
    int word_w = 0;
    std::string word_active;

    auto flush_line = [&]() {
        out.push_back(cur + U_RESET);
        cur = indent + active;
        cur_w = (int)indent.size();
    };
    auto push_word = [&]() {
        if (word.empty())
            return;
        if (word_w == 0) // only escape sequences: attach without spacing
        {
            cur += word;
            active = word_active;
            word.clear();
            return;
        }
        bool at_start = cur_w <= (int)std::max(indent.size(), out.empty() ? lead : 0);
        if (!at_start && cur_w + 1 + word_w > width)
        {
            flush_line();
            at_start = true;
        }
        if (!at_start)
        {
            cur += " ";
            cur_w++;
        }
        // hard-split words longer than a full line
        while (cur_w + word_w > width && width - cur_w > 0)
        {
            size_t cut = prefix_bytes(word, width - cur_w);
            if (cut == 0)
                break;
            std::string part = word.substr(0, cut);
            cur += part;
            cur_w += display_width(part);
            word = word.substr(cut);
            word_w = display_width(word);
            flush_line();
        }
        cur += word;
        cur_w += word_w;
        active = word_active;
        word.clear();
        word_w = 0;
    };

    size_t i = start_i;
    word_active = active;
    while (i < text.size())
    {
        size_t esc = escape_len(text, i);
        if (esc)
        {
            std::string seq = text.substr(i, esc);
            word += seq;
            if (seq == "\033[0m" || seq == "\033[m")
                word_active.clear();
            else if (seq.back() == 'm')
                word_active += seq;
            i += esc;
            continue;
        }
        if (text[i] == ' ')
        {
            push_word();
            i++;
            continue;
        }
        size_t start = i;
        word_w += codepoint_width(decode_utf8(text, i));
        word += text.substr(start, i - start);
    }
    push_word();
    if (display_width(cur) > (int)indent.size() || out.empty())
        out.push_back(cur);
    return (out);
}

std::string center(const std::string &s, int cw)
{
    if (cw < 0)
        cw = text_width();
    int w = display_width(s);
    if (w >= cw)
        return (s);
    int left = (cw - w) / 2;
    return (std::string(left, ' ') + s + std::string(cw - w - left, ' '));
}

void clear(void)
{
    std::cout << U_CLEAR;
}

static std::string rep(const char *s, int n)
{
    std::string out;
    for (int i = 0; i < n; i++)
        out += s;
    return (out);
}

static void border_row(const std::string &left, const std::string &right)
{
    std::cout << margin_str() << U_CYAN << left << rep("═", border_width() - 2) << right << U_RESET << "\n";
}

static void raw_line(const std::string &text)
{
    int pad_w = text_width() - display_width(text);
    std::cout << margin_str() << U_CYAN << "║ " << U_RESET
              << text << U_RESET
              << std::string(pad_w < 0 ? 0 : pad_w, ' ')
              << U_CYAN << " ║" << U_RESET << "\n";
}

void line(const std::string &text)
{
    std::vector<std::string> rows = wrap(text, text_width());
    for (size_t i = 0; i < rows.size(); i++)
        raw_line(rows[i]);
}

void plain(const std::string &text)
{
    std::cout << "  " << text << "\n";
}

void blank(void)
{
    line("");
}

void sep(void)
{
    std::cout << margin_str() << U_CYAN << "╠" << rep("═", border_width() - 2) << "╣" << U_RESET << "\n";
}

void frame_open(const std::string &title, bool with_logo)
{
    cached_border = 0;
    cached_margin = -1;
    clear();
    border_row(UI_TL, UI_TR);
    blank();
    if (with_logo && logo())
        blank();
    line_center(title, std::string(U_BOLD) + U_WHITE);
    sep();
}

void frame_close(void)
{
    border_row(UI_BL, UI_BR);
}

void line_center(const std::string &text, const std::string &color)
{
    std::vector<std::string> rows = wrap(text, text_width());
    for (size_t i = 0; i < rows.size(); i++)
        raw_line(color + center(rows[i]) + U_RESET);
}

void line_right(const std::string &text, const std::string &color)
{
    int w = display_width(text);
    int room = text_width() - w;
    raw_line(std::string(room > 0 ? room : 0, ' ') + color + text + U_RESET);
}

void line_kv(const std::string &label, const std::string &value, const std::string &vcolor)
{
    std::string row = U_DIM + label + U_RESET + "  " + vcolor + value + U_RESET;
    line(row);
}

static const char *LOGO_L[] = {
    "   _____ ________    ___________                      ",
    "  /  |  |\\_____  \\   \\_   _____/__  ________    _____  ",
    " /   |  |_/  ____/    |    __)_\\  \\/  /\\__  \\  /     \\ ",
    "/    ^   /       \\    |        \\>    <  / __ \\|  Y Y  \\",
    "\\____   |\\_______ \\  /_______  /__/\\_ (____  /__|_|  /",
    "     |__|        \\/          \\/      \\/     \\/      \\/ ",
};
static const int LOGO_ROWS = 6;

static int logo_width(void)
{
    int w = 0;
    for (int i = 0; i < LOGO_ROWS; i++)
        w = std::max(w, display_width(LOGO_L[i]));
    return (w);
}

bool logo(void)
{
    int w = logo_width();
    if (text_width() < w)
        return (false);
    for (int i = 0; i < LOGO_ROWS; i++)
    {
        // pad every row to the same width so the art stays aligned once centered
        std::string row = pad(LOGO_L[i], w);
        raw_line(std::string(U_CYAN) + U_BOLD + center(row) + U_RESET);
    }
    return (true);
}

static std::string card_row(const std::string &content, int cw)
{
    std::string inner = "│ " + pad(truncate(content, cw - 4), cw - 4) + " │";
    return (inner);
}

void card(int num, const std::string &title, const std::string &desc)
{
    int cw = std::min(text_width() - 4, 54);
    if (cw < 24)
        cw = std::min(24, text_width());
    std::string num_s = std::to_string(num);
    line_center("┌" + rep("─", cw - 2) + "┐", U_CYAN);
    line_center(card_row(std::string(U_YELLOW) + U_BOLD + "[" + num_s + "]" + U_RESET
                             + "  " + std::string(U_WHITE) + U_BOLD + title + U_RESET,
                         cw),
                U_WHITE);
    if (!desc.empty())
    {
        std::string indent(std::string("[" + num_s + "]  ").size(), ' ');
        line_center(card_row(indent + std::string(U_GRAY) + desc + U_RESET, cw), U_WHITE);
    }
    line_center("└" + rep("─", cw - 2) + "┘", U_CYAN);
}

std::string progress(double pct, int len)
{
    if (pct < 0)
        pct = 0;
    if (pct > 100)
        pct = 100;
    int filled = (int)(pct / 100.0 * len);
    std::string color = U_GREEN;
    if (pct < 50)
        color = U_YELLOW;
    if (pct < 25)
        color = U_RED;
    std::string bar;
    for (int i = 0; i < len; i++)
        bar += (i < filled) ? "▓" : "░";
    return (color + bar + U_RESET);
}

std::string badge(const std::string &s, const std::string &color)
{
    return (color + U_BOLD + " " + s + " " + U_RESET);
}

void prompt(const std::string &msg)
{
    std::cout << U_YELLOW << "╰─▶ " << U_RESET << U_BOLD << msg << U_RESET << "  ";
    std::cout.flush();
}

static std::string trim(const std::string &s)
{
    size_t b = s.find_first_not_of(" \t\r");
    if (b == std::string::npos)
        return ("");
    size_t e = s.find_last_not_of(" \t\r");
    return (s.substr(b, e - b + 1));
}

// stdin closed (Ctrl+D / pipe end): leave cleanly instead of looping forever
static void on_eof(void)
{
    std::cout << "\n" << U_YELLOW << U_BOLD << "   Disconnected (end of input)." << U_RESET << std::endl;
    std::exit(0);
}

std::string ask(const std::string &msg)
{
    prompt(msg);
    std::string input;
    if (!std::getline(std::cin, input))
        on_eof();
    return (trim(input));
}

void press_enter(const std::string &msg)
{
    prompt(msg);
    std::string input;
    if (!std::getline(std::cin, input))
        on_eof();
}

} // namespace ui
