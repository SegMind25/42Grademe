#include "exam.hpp"

std::string current_path(void)
{
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        return (".");
    std::string current_path = cwd;
    free(cwd);
    const char *home = getenv("HOME");
    if (home && *home && current_path.compare(0, strlen(home), home) == 0)
        current_path.replace(0, strlen(home), "~");
    return (current_path);
}

std::string remaining_time(time_t end_time)
{
    time_t remaining_time = end_time - time(0);
    if (remaining_time <= 0)
        return ("time is over");
    int hours = remaining_time / 3600;
    int minutes = (remaining_time % 3600) / 60;
    int seconds = remaining_time % 60;
    std::stringstream ss;
    ss << hours << "h " << std::setw(2) << std::setfill('0') << minutes << "m "
       << std::setw(2) << std::setfill('0') << seconds << "s";
    return (ss.str());
}

void sigd(void)
{
    ui::clear();
    std::cout << U_YELLOW << U_BOLD << "   You have been disconnected after using Ctrl+D" << U_RESET << std::endl;
    exit(0);
}

void sigc(int sig)
{
    ui::clear();
    if (sig == SIGINT)
        std::cout << U_YELLOW << U_BOLD << "   You have been disconnected after using Ctrl+C" << U_RESET << std::endl;
    else if (sig == SIGQUIT)
        std::cout << U_YELLOW << U_BOLD << "   You have been disconnected after using Ctrl+\\ (SIGQUIT)" << U_RESET << std::endl;
    else
        std::cout << U_YELLOW << U_BOLD << "   Exit exam..." << U_RESET << std::endl;
    std::cout << U_DIM << "   Your progress is saved, run " << U_RESET << U_LIME << "make" << U_RESET
              << U_DIM << " again to restore it." << U_RESET << std::endl;
    exit(0);
}

bool file_exists(std::string path)
{
    struct stat st;
    return (stat(path.c_str(), &st) == 0);
}

void ensure_dir(const std::string &path)
{
    mkdir(path.c_str(), 0755);
}

void open_url(const std::string &url)
{
#ifdef __linux__
    std::string cmd = "xdg-open '" + url + "' >/dev/null 2>&1 &";
#else
    std::string cmd = "open '" + url + "' >/dev/null 2>&1 &";
#endif
    if (system(cmd.c_str()) != 0)
        ui::plain(U_DIM + "Open this link in your browser: " + U_RESET + U_LIME + url + U_RESET);
}

// Anonymous usage log (runs in background, never blocks the UI)
void send_data(const std::string &event)
{
    std::string safe;
    for (size_t i = 0; i < event.size(); i++)
        if (event[i] != '"' && event[i] != '\\' && event[i] != '$' && event[i] != '`')
            safe += event[i];
    std::string cmd = "bash .system/data_sender.sh \"" + safe + "\" >/dev/null 2>&1 &";
    if (system(cmd.c_str()) != 0)
        return;
}

// ==> Reset folder to default
bool exam::clean_all()
{
    if (level == 0)
        system("rm -rf rendu");
    system("rm -rf subjects .system/grading .dev");
    return (true);
}

void reset_folder(void)
{
    system("rm -rf .system/grading/* rendu/* subject traces a.out a.out.dSYM");
}

// ==> Return the minutes to wait relative to assignement number
double exercise::grade_time(void)
{
    // fibonacci-like growth: 0.5, 2.5, 3, 5.5, 8.5, ...
    if (get_assignement() <= 0)
        return (0);
    double a = 0.5;
    double b = 2.5;
    for (int i = 1; i < get_assignement(); i++)
    {
        double next = a + b;
        a = b;
        b = next;
    }
    return (a);
}
