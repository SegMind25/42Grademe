#include "exam.hpp"

std::string current_path(void)
{
    std::string current_path = getcwd(NULL, 0);
    const char *home = getenv("HOME");
    if (home && current_path.find(home) != std::string::npos)
        current_path.replace(current_path.find(home), std::string(home).length(), "~");
    return (current_path);
}

std::string time_in_string(time_t rawtime)
{
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H:%M:%S", timeinfo);
    std::string str(buffer);

    return (str);
}

std::string remaining_time(time_t end_time)
{
    time_t now = time(0);
    time_t remaining_time = end_time - now;
    if (remaining_time < 0)
        return ("0");
    int hours = remaining_time / 3600;
    int minutes = (remaining_time % 3600) / 60;
    int seconds = (remaining_time % 3600) % 60;
    std::stringstream ss;
    ss << hours << "hrs, " << std::setw(2) << minutes << "min and " << std::setw(2) << seconds << "sec";
    return (ss.str());
}

std::string lastupdate(time_t end_time)
{
    time_t now = 1662477376;
    time_t remaining_time = end_time - now;
    int day = remaining_time / 86400;
    int hours = (remaining_time % 86400) / 3600;
    std::string ret = MAGENTA + std::to_string(day) + RESET + " days and " + MAGENTA + std::to_string(hours) + RESET + " hours";
    return (ret);
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
    if (sig == SIGQUIT)
        std::cout << U_YELLOW << U_BOLD << "   You have been disconnected after using Ctrl+\\ (SIGQUIT)" << U_RESET << std::endl;
    if (sig == SIGTSTP)
        std::cout << U_YELLOW << U_BOLD << "   Exit exam..." << U_RESET << std::endl;
    exit(0);
}

bool file_exists(std::string path)
{
    std::ifstream infile(path);
    return infile.good();
}

// ==> Reset folder to default
bool exam::clean_all()
{
    if (file_exists("rendu") && level == 0)
        system("rm -rf rendu");
    if (file_exists("subjects"))
        system("rm -rf subjects");
    if (file_exists(".system/grading"))
        system("rm -rf .system/grading");
    if (file_exists(".system/grading/passed"))
        system("rm -rf .system/grading/passed");
    if (file_exists(".dev"))
        system("rm -f .dev");
    return (true);
}

void reset_folder(void)
{
    system("rm -rf .system/grading/*");
    system("rm -rf rendu/*");
    system("rm -rf subject");
    system("rm -rf traces");
    system("rm -rf a.out");
    system("rm -rf a.out.dSYM");
}

// ==> Return the minutes to wait relative to assignement number
double exercise::grade_time(void)
{
    // do a vector contain all the fibonnaci numbers
    std::vector<double> fib;
    if (get_assignement() == 0)
        return (0);
    fib.push_back(0.5);
    fib.push_back(2.5);
    for (int i = 2; i < 100; i++)
    {
        fib.push_back(fib[i - 1] + fib[i - 2]);
        if (i - 2 == get_assignement() - 1)
            return (fib[i - 2]);
    }
    return (0);
}

// ==> FEATURE: Check if readline is installed on the system
void check_readline()
{
    // if readline is not installed
    int is_linux = 0;
#ifdef __linux__
    is_linux = 1;
#endif

    if (!file_exists("/usr/include/readline/readline.h") && is_linux)
    {
        ui::clear();
        ui::frame_open("MISSING READLINE", false);
        ui::blank();
        ui::line(U_RED + "  Error: readline is not installed on your computer." + U_RESET);
        ui::blank();
        ui::frame_close();
        ui::prompt("Auto install readline? [y/n]");
        std::string input;
        std::getline(std::cin, input);
        if (input == "y")
        {
            std::cout << "  Installing readline..." << std::endl;
            system("sudo apt-get install libreadline-dev");
            std::cout << "  Readline installed, please restart the program" << std::endl;
            exit(0);
        }
        else
        {
            std::cout << "  Readline is required to use this program, please install it and restart the program" << std::endl;
            exit(0);
        }
        exit(0);
    }
}