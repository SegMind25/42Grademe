#!/bin/bash
# 42_EXAM launcher: checks dependencies, compiles the examshell and starts it.

version="2.2"
cd "$(dirname "$0")/.." || exit 1

BOLD="\033[1m"
RED="\033[31m"
GREEN="\033[32m"
GRAY="\033[90m"
MAGENTA="\033[35m"
WHITE="\033[37m"
RESET="\033[0m"
CLEAR_LINE="\r\033[2K"
SPIN=("⠋" "⠙" "⠹" "⠸" "⠼" "⠴" "⠦" "⠧" "⠇" "⠏")

ok()   { printf "${CLEAR_LINE}${GREEN}${BOLD}✔${RESET} %b\n" "$1"; }
fail() { printf "${CLEAR_LINE}${RED}${BOLD}✗${RESET} %b\n" "$1"; }
info() { printf "${CLEAR_LINE}${GRAY}  ➫ %b${RESET}\n" "$1"; }

# spin <pid> <message>: animate while <pid> is running
spin() {
    local pid=$1 msg=$2 i=0
    while kill -0 "$pid" 2>/dev/null; do
        printf "${CLEAR_LINE}${WHITE}%s${RESET} %b" "${SPIN[i]}" "$msg"
        i=$(( (i + 1) % ${#SPIN[@]} ))
        sleep 0.08
    done
}

# run_step <message> <command...>: run a command with a spinner, return its status
run_step() {
    local msg=$1; shift
    "$@" >/dev/null 2>.system/.devmake.err &
    local pid=$!
    spin "$pid" "$msg"
    wait "$pid"
}

rm -f .system/a.out .system/.devmake.err
[ "$1" != "grade" ] && [ "$1" != "gradejustinstall" ] && clear
printf "\n${BOLD}${MAGENTA}  42_EXAM${RESET} ${GRAY}v$version${RESET}\n\n"

# ---- 1. compilers --------------------------------------------------------
missing=""
for tool in gcc g++; do
    command -v "$tool" >/dev/null 2>&1 || missing="$missing $tool"
done
if [ -n "$missing" ]; then
    fail "Missing compiler:${BOLD}$missing${RESET}"
    info "Install it first (e.g. ${WHITE}sudo apt-get install build-essential${GRAY} or ${WHITE}xcode-select --install${GRAY})"
    exit 1
fi
ok "Compilers found"

# ---- 2. updates (only when online) ---------------------------------------
if [ "$1" != "gradejustinstall" ]; then
    if run_step "Checking for updates" curl -s --max-time 3 -o /dev/null https://github.com; then
        if [ -d .git ]; then
            git pull --ff-only >/dev/null 2>&1 &
        fi
        ok "Online ${GRAY}— you have the latest version v$version${RESET}"
    else
        fail "Offline ${GRAY}— local launch${RESET}"
    fi
fi

# ---- 3. readline ---------------------------------------------------------
readline_ok() {
    g++ .system/checkreadline.cpp -lreadline -o .system/readline_ok >/dev/null 2>&1
    local status=$?
    rm -f .system/readline_ok
    return $status
}

if run_step "Checking readline library" readline_ok; then
    ok "Readline library"
else
    fail "Readline library not installed"
    if command -v apt-get >/dev/null 2>&1; then
        info "Installing libreadline-dev with apt-get (sudo password may be asked)..."
        sudo apt-get install -y libreadline-dev
    elif command -v dnf >/dev/null 2>&1; then
        info "Installing readline-devel with dnf (sudo password may be asked)..."
        sudo dnf install -y readline-devel
    elif command -v yum >/dev/null 2>&1; then
        info "Installing readline-devel with yum (sudo password may be asked)..."
        sudo yum install -y readline-devel
    elif command -v brew >/dev/null 2>&1; then
        info "Installing readline with brew..."
        brew install readline
    fi
    if ! readline_ok; then
        fail "Can't install the readline library automatically"
        info "1. Check that g++ is installed"
        info "2. Install libreadline-dev (Debian/Ubuntu) or readline-devel (Fedora) manually"
        info "3. Still stuck? Open an issue on Github"
        exit 1
    fi
    ok "Readline library installed"
fi

# ---- 4. compile ----------------------------------------------------------
SOURCES=".system/ui.cpp .system/exercise.cpp .system/main.cpp .system/menu.cpp .system/exam.cpp \
.system/utils.cpp .system/grade_request.cpp .system/data_persistence.cpp"

# shellcheck disable=SC2086
if ! run_step "Compiling ${MAGENTA}${BOLD}42_EXAM${RESET}" g++ -std=c++11 -O2 $SOURCES -lreadline -o .system/a.out; then
    fail "Compilation of ${MAGENTA}${BOLD}42_EXAM${RESET}"
    printf "\n${RED}${BOLD}Oops!${RESET}${BOLD} Something went wrong during the compilation...${RESET}\n"
    echo "Please open an issue on the Github repo and include:"
    echo ""
    printf "  - Your OS: ${GRAY}%s${RESET}\n" "$(uname -a)"
    printf "  - The error message:${GRAY}\n"
    cat .system/.devmake.err
    printf "${RESET}\nThanks for your contribution!\n"
    exit 1
fi
rm -f .system/.devmake.err
ok "Compiled ${MAGENTA}${BOLD}42_EXAM${RESET}"
chmod +x .system/a.out

[ "$1" = "gradejustinstall" ] && exit 0

# ---- 5. login ------------------------------------------------------------
if [ -z "$USER" ]; then
    if [ -f .system/.env ]; then
        USER=$(sed 's/^USER=//' .system/.env | head -n 1)
    fi
    if [ -z "$USER" ]; then
        printf "\n${BOLD}USER is not set.${RESET} Enter your 42 login: "
        read -r USER
        echo "$USER" > .system/.env
    fi
    export USER
    ok "Login set to ${BOLD}$USER${RESET}"
fi

export LOGNAMELOG42EXAM="${LOGNAME:-$USER}"
sleep 0.3
./.system/a.out
