#include "exam.hpp"

// ==> CGV Acceptation

void CGVAcceptation(void)
{
    ui::frame_open("TERMS & CONDITIONS", false);
    ui::blank();
    ui::line(U_BOLD + "You must accept these rules to use this program:" + U_RESET);
    ui::blank();
    std::ifstream file(".system/CGV.txt");
    std::string line;
    while (std::getline(file, line))
        ui::line("  " + U_WHITE + line + U_RESET);
    ui::blank();
    ui::line(U_BOLD + "Type " + U_LIME + "agree" + U_RESET + U_BOLD + " to accept and continue." + U_RESET);
    ui::frame_close();
    ui::prompt(U_BOLD + "Do you agree? (type 'agree')" + U_RESET);
    std::string input;
    std::getline(std::cin, input);
    if (input != "agree")
    {
        ui::clear();
        ui::frame_open("GOODBYE", false);
        ui::blank();
        ui::line("You must accept these rules to use this program.");
        ui::blank();
        ui::frame_close();
        exit(0);
    }
    else
    {
        std::ofstream file(".system/acceptCGV");
        file << "1";
        file.close();
        // thanks for accepting
        ui::clear();
        ui::frame_open("WELCOME", false);
        ui::blank();
        ui::line_center(U_LIME + U_BOLD + "Thanks for accepting these rules, and good luck for your exam! 🍀" + U_RESET, U_WHITE);
        ui::blank();
        ui::frame_close();
        sleep(2);
    }
}

// ==> Shell prompt
void exam::exam_prompt(void)
{
    std::string input;
    int is_linux = 0;
#ifdef __linux__
    is_linux = 1;
#endif

    while (1)
    {
        char *line = readline("\e[96m┌─\e[0m\e[93m examshell \e[0m\e[96m─\e[0m\e[97m›\e[0m ");
        if (line == NULL)
            sigd();
        input = line;
        while (input.back() == ' ')
            input.pop_back();
        while (input.front() == ' ')
            input.erase(input.begin());
        if (input.empty())
            continue;
        add_history(input.c_str());
        if ((input == "remove_grade_time" || input == "new_ex" || input == "force_success") && !setting_dcc)
            ui::plain(U_YELLOW + "⚠  Cheat commands are currently disabled, use " + U_LIME + U_BOLD + "settings" + U_RESET + U_YELLOW + " command." + U_RESET);
        else if (input == "finish" || input == "exit" || input == "quit")
        {
            ui::clear();
            ui::frame_open("EXIT EXAM", false);
            ui::blank();
            ui::line("  Are you sure you want to " + U_RED + "exit" + U_RESET + " the exam?");
            ui::line("  All your progress will be " + U_RED + U_BOLD + "lost" + U_RESET + ".");
            ui::line("  Type " + U_LIME + U_BOLD + "yes" + U_RESET + " to confirm.");
            ui::blank();
            ui::frame_close();
            ui::prompt(U_RED + "Confirm exit? [yes]" + U_RESET);
            std::string input;
            std::getline(std::cin, input);
            if (input == "yes")
            {
                if (std::ifstream(".system/exam_token/current_token.txt"))
                    remove(".system/exam_token/current_token.txt");
                exit(0);
            }
            else
                std::cout << "  ** Abort ** " << std::endl;
        }
        else if (input == "settings")
        {
            changex = 1;
            settings_menu();
            if (vip)
                infovip();
            else
                info();
        }
        else if (input == "grademe")
        {
            grademe();
        }
        else if (input == "status")
        {
            changex = 1;
            if (vip)
                infovip();
            else
                info();
        }
        else if (input == "new_ex")
        {
            change_ex();
            using_cheatcode++;
        }
        else if (input == "force_success")
        {
            if (!vip)
            {
                std::cout << "  " << U_PINK << "'force_success'" << U_RESET << " is a Grademe+ command, contribute by making a Pull Request or support with command " << U_LIME << "sponsor" << U_RESET << std::endl;
            }
            else
            {
                using_cheatcode++;
                success_ex(1);
            }
        }
        else if (input == "help")
        {
            exam_help();
        }
        else if (input == "sponsor")
        {
            ui::clear();
            ui::frame_open("SPONSOR", false);
            ui::blank();
            ui::line_center(U_TEAL + U_BOLD + "A word from the creator:" + U_RESET, U_WHITE);
            ui::blank();
            ui::line(U_WHITE + "  This program has been created entirely " + U_LIME + "for free" + U_RESET + U_WHITE + " and " + U_LIME + "open-source" + U_RESET + U_WHITE + "." + U_RESET);
            ui::line(U_WHITE + "  The VIP option exists not to create a business, but simply to help" + U_RESET);
            ui::line(U_WHITE + "  those who enjoy using the program and have a little extra to give." + U_RESET);
            ui::line(U_WHITE + "  If you're a student who loves this tool and wants to support my journey," + U_RESET);
            ui::line(U_WHITE + "  consider becoming a VIP by making a small donation." + U_RESET);
            ui::line(U_WHITE + "  However, if you prefer to contribute without spending money, " + U_PINK + U_BOLD + "you can" + U_RESET);
            ui::line(U_PINK + U_BOLD + "  always help out by making a Pull Request" + U_RESET + U_WHITE + ". I would welcome your support" + U_RESET);
            ui::line(U_WHITE + "  with open arms." + U_RESET);
            ui::line(U_WHITE + "  For those who are just starting out, or can't contribute financially," + U_RESET);
            ui::line(U_WHITE + "  you can also email me explaining why you'd like VIP status, and I'll" + U_RESET);
            ui::line(U_WHITE + "  be happy to grant it to you." + U_RESET);
            ui::line(U_WHITE + "  The VIP status does not limit the program's core features. It simply" + U_RESET);
            ui::line(U_WHITE + "  offers two small additional options for those who wish to support the project." + U_RESET);
            ui::line(U_GREEN + U_BOLD + "  Thank you for your support, and happy coding! ♥" + U_RESET);
            ui::blank();
            ui::frame_close();
            ui::press_enter("Press any key to open the sponsor page...");

            if (is_linux)
                std::system("xdg-open http://sponsor.grademe.fr");
            else
                std::system("open http://sponsor.grademe.fr");
            ui::clear();
            ui::frame_open("THANK YOU", false);
            ui::blank();
            ui::line_center(U_GREEN + U_BOLD + "Thanks a lot ♥" + U_RESET, U_WHITE);
            ui::blank();
            ui::frame_close();
            if (vip)
                infovip();
            else
                info();
        }
        else if (input == "repo_git")
        {
            std::string tmp = "bash .system/data_sender.sh \"cheatcode:repo_git\"";
            system(tmp.c_str());
            ui::plain(U_WHITE + "Opening git repo..." + U_RESET);
            if (is_linux)
                std::system("xdg-open http://git.grademe.fr");
            else
                std::system("open http://git.grademe.fr");
        }
        else if (input == "remove_grade_time")
        {
            std::string tmp = "bash .system/data_sender.sh \"cheatcode:remove_grade_time\"";
            system(tmp.c_str());
            ui::plain(U_LIME + "✔  Time between grading is now removed for this exam" + U_RESET);
            waiting_time = false;
            using_cheatcode++;
        }
        else if (input == "gradenow" && vip)
        {
            grade_request(1);
        }
        else if (input == "")
            std::cout << REMOVE_LINE;
        else if (input != "")
            std::cout << "  " << U_RED << "✘ Unknown command" << U_RESET << "  — type " << U_LIME << "help" << U_RESET << " for more help" << std::endl;
        // info();
    }
}
// jo je taime

// ==> Starting a new exercise/exam
bool exam::start_new_ex(void)
{
    load_settings();
    if (!backup)
    {
        list_ex_lvl = list_dir();
        exercise ex = *randomize_exercise(list_ex_lvl, setting_dse);
        current_ex = new exercise(ex);
        prepare_current_ex();
        store_data();
    }
    if (vip)
        infovip();
    else
        info();
    exam_prompt();
    return (true);
}

int main(int argc, char **argv)
{
    signal(SIGINT, sigc);
    signal(SIGQUIT, sigc);
    signal(SIGTERM, sigc);

    if (file_exists("a.out"))
        remove("a.out");

    exam exm;

    // Adding CGV Acceptation
    if (!file_exists(".system/acceptCGV"))
        CGVAcceptation();

    if (file_exists(".system/exam_token/current_token.txt"))
        exm.restore_data();
    else
        exm.ask_param();

    exm.start_new_ex();

    return (0);
}