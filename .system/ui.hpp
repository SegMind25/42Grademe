#pragma once

#include <string>
#include <vector>
#include <functional>

// ---- extended ANSI helpers (kept short to not clash with exam.hpp macros) ----
#define U_BOLD std::string("\e[1m")
#define U_DIM std::string("\e[2m")
#define U_ITALIC std::string("\e[3m")
#define U_UNDERLINE std::string("\e[4m")
#define U_RESET std::string("\e[0m")
#define U_BLACK std::string("\e[30m")
#define U_RED std::string("\e[91m")
#define U_GREEN std::string("\e[92m")
#define U_LIME std::string("\e[92m")
#define U_YELLOW std::string("\e[93m")
#define U_BLUE std::string("\e[94m")
#define U_MAGENTA std::string("\e[95m")
#define U_CYAN std::string("\e[96m")
#define U_WHITE std::string("\e[97m")
#define U_GRAY std::string("\e[90m")
#define U_ORANGE std::string("\e[38;5;208m")
#define U_PINK std::string("\e[38;5;205m")
#define U_GOLD std::string("\e[38;5;178m")
#define U_TEAL std::string("\e[38;5;80m")
#define U_CLEAR std::string("\e[H\e[2J\e[3J")

// Box drawing characters
#define UI_H "═"
#define UI_V "║"
#define UI_TL "╔"
#define UI_TR "╗"
#define UI_BL "╚"
#define UI_BR "╝"
#define UI_T "╠"
#define UI_S "╣"

namespace ui {

// ---- dimensions ----
int border_width(void);     // full box width (incl. corners)
int text_width(void);       // area between "║ " and " ║"
int display_width(const std::string &s); // width ignoring ANSI escapes

// ---- core primitives ----
void clear(void);
void frame_open(const std::string &title, bool with_logo = false);
void frame_close(void);
void blank(void);
void sep(void);
void line(const std::string &text = "");
void plain(const std::string &text = "");
void line_center(const std::string &text, const std::string &color = U_WHITE);
void line_right(const std::string &text, const std::string &color = U_GRAY);
void line_kv(const std::string &label, const std::string &value,
             const std::string &vcolor = U_WHITE);

// ---- text helpers ----
std::string center(const std::string &s, int cw = -1);
std::string pad(const std::string &s, int cw = -1);

// ---- decorative components ----
void logo(void);                                        // big "42EXAM" block
void card(int num, const std::string &title, const std::string &desc = "");
std::string progress(double pct, int len = 24);          // ▓░░ bar
std::string badge(const std::string &s, const std::string &color);

// ---- interactive helpers ----
void prompt(const std::string &msg = "Enter your choice");
void press_enter(const std::string &msg = "Press Enter to continue...");
std::string ask(const std::string &msg);                 // prompt + read line

} // namespace ui
