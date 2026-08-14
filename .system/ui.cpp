#include "ui.hpp"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/ioctl.h>

namespace ui {

static int cached_border = 0;

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
        cached_border = std::min(t, 80);
        if (cached_border < 68)
            cached_border = 68;
    }
    return (cached_border);
}

int text_width(void)
{
    return (border_width() - 4);
}

int display_width(const std::string &s)
{
    int w = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        unsigned char c = (unsigned char)s[i];
        if (c == '\e' && i + 1 < s.size() && s[i + 1] == '[')
        {
            while (i < s.size() && s[i] != 'm')
                i++;
        }
        else if ((c & 0xC0) == 0x80)
            continue;
        else
            w++;
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
    std::cout << U_CYAN << left << rep("═", border_width() - 2) << right << U_RESET << "\n";
}

void line(const std::string &text)
{
    int pad_w = text_width() - display_width(text);
    std::cout << U_CYAN << "║ " << U_RESET
              << text
              << std::string(pad_w < 0 ? 0 : pad_w, ' ')
              << U_CYAN << " ║" << U_RESET << "\n";
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
    std::cout << U_CYAN << "╠" << rep("═", border_width() - 2) << "╣" << U_RESET << "\n";
}

void frame_open(const std::string &title, bool with_logo)
{
    clear();
    border_row(UI_TL, UI_TR);
    blank();
    if (with_logo)
    {
        logo();
        blank();
    }
    line_center(title, std::string(U_BOLD) + U_WHITE);
    sep();
}

void frame_close(void)
{
    border_row(UI_BL, UI_BR);
}

void line_center(const std::string &text, const std::string &color)
{
    line(color + center(text) + U_RESET);
}

void line_right(const std::string &text, const std::string &color)
{
    line(pad("") + color + text + U_RESET);
}

void line_kv(const std::string &label, const std::string &value, const std::string &vcolor)
{
    std::string row = U_DIM + label + U_RESET + "  " + vcolor + value + U_RESET;
    line(row);
}

static const char *LOGO_L[] = {
    "██╗  ██╗██████╗",
    "╚██╗██╔╝╚════██╗",
    " ╚███╔╝  █████╔╝",
    " ██╔██╗  ╚═══██╗",
    "██╔╝ ██╗██████╔╝",
    "╚═╝  ╚═╝╚═════╝ ",
};

static const char *LOGO_R[] = {
    "██████╗ ███████╗ █████╗ ███╗   ███╗",
    "██╔══██╗██╔════╝██╔══██╗████╗ ████║",
    "██████╔╝█████╗  ███████║██╔████╔██║",
    "██╔══██╗██╔══╝  ██╔══██║██║╚██╔╝██║",
    "██║  ██║███████╗██║  ██║██║ ╚═╝ ██║",
    "╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝",
};

void logo(void)
{
    for (int i = 0; i < 6; i++)
    {
        std::string row = std::string(U_YELLOW) + U_BOLD + LOGO_L[i] + U_RESET
                          + "    " + std::string(U_CYAN) + U_BOLD + LOGO_R[i] + U_RESET;
        line_center(row, U_WHITE);
    }
}

static std::string card_row(const std::string &content, int cw)
{
    std::string inner = "│ " + pad(content, cw - 4) + " │";
    return (inner);
}

void card(int num, const std::string &title, const std::string &desc)
{
    int cw = 50;
    std::string num_s = std::to_string(num);
    line_center("┌" + rep("─", cw - 2) + "┐", U_CYAN);
    line_center(card_row(std::string(U_YELLOW) + U_BOLD + "[" + num_s + "]" + U_RESET
                             + "  " + std::string(U_WHITE) + U_BOLD + title + U_RESET,
                         cw),
                U_WHITE);
    if (!desc.empty())
        line_center(card_row("       " + std::string(U_GRAY) + desc + U_RESET, cw), U_WHITE);
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

std::string ask(const std::string &msg)
{
    prompt(msg);
    std::string input;
    if (!std::getline(std::cin, input))
        input = "";
    return (input);
}

void press_enter(const std::string &msg)
{
    prompt(msg);
    std::string input;
    std::getline(std::cin, input);
}

} // namespace ui
