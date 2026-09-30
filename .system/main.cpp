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
    std::string input = ui::ask("Do you agree? (type 'agree')");
    if (input != "agree")
    {
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
    while (1)
    {
        char *line = readline("\033[96m┌─\033[0m\033[93m examshell \033[0m\033[96m─\033[0m\033[97m›\033[0m ");
        if (line == NULL)
            sigd();
        std::string input = line;
        free(line);
        size_t b = input.find_first_not_of(" \t");
        input = (b == std::string::npos) ? "" : input.substr(b, input.find_last_not_of(" \t") - b + 1);
        if (input.empty())
            continue;
        add_history(input.c_str());

        if (time(0) >= end_time && input != "finish" && input != "exit" && input != "quit")
            time_over();

        bool cheat = (input == "remove_grade_time" || input == "new_ex" || input == "force_success");
        if (cheat && !setting_dcc)
            ui::plain(U_YELLOW + "⚠  Cheat commands are disabled, enable them with the " + U_LIME + U_BOLD + "settings" + U_RESET + U_YELLOW + " command." + U_RESET);
        else if (input == "finish" || input == "exit" || input == "quit")
        {
            ui::frame_open("EXIT EXAM", false);
            ui::blank();
            ui::line("  Are you sure you want to " + U_RED + "exit" + U_RESET + " the exam?");
            ui::line("  All your progress will be " + U_RED + U_BOLD + "lost" + U_RESET + ".");
            ui::blank();
            ui::line("  " + U_DIM + "Tip: Ctrl+C quits but keeps your progress for next time." + U_RESET);
            ui::blank();
            ui::frame_close();
            std::string confirm = ui::ask(U_RED + "Type 'yes' to confirm" + U_RESET);
            if (confirm == "yes")
            {
                remove(TOKEN_FILE);
                ui::clear();
                ui::plain(U_LIME + "Exam closed. See you soon! 👋" + U_RESET);
                exit(0);
            }
            ui::plain(U_DIM + "Aborted." + U_RESET);
        }
        else if (input == "settings")
        {
            changex = 1;
            settings_menu();
            info();
        }
        else if (input == "grademe")
            grademe();
        else if (input == "status")
        {
            changex = 1;
            info();
        }
        else if (input == "new_ex")
        {
            using_cheatcode++;
            change_ex();
        }
        else if (input == "force_success")
        {
            if (!vip)
                ui::plain(U_PINK + "force_success" + U_RESET + " is a VIP command, contribute with a Pull Request or type " + U_LIME + "sponsor" + U_RESET + ".");
            else
            {
                using_cheatcode++;
                success_ex(1);
            }
        }
        else if (input == "gradenow")
        {
            if (!vip)
                ui::plain(U_PINK + "gradenow" + U_RESET + " is a VIP command, contribute with a Pull Request or type " + U_LIME + "sponsor" + U_RESET + ".");
            else
                grade_request(1);
        }
        else if (input == "help")
            exam_help();
        else if (input == "sponsor")
        {
            ui::frame_open("SPONSOR", false);
            ui::blank();
            sponsor_message();
            ui::blank();
            ui::frame_close();
            std::string open = ui::ask("Open the sponsor page? [y/N]");
            if (open == "y" || open == "Y")
                open_url("http://sponsor.grademe.fr");
            info();
        }
        else if (input == "repo_git")
        {
            send_data("cheatcode:repo_git");
            ui::plain(U_WHITE + "Opening git repo..." + U_RESET);
            open_url("http://git.grademe.fr");
        }
        else if (input == "remove_grade_time")
        {
            send_data("cheatcode:remove_grade_time");
            ui::plain(U_LIME + "✔  Time between grading is now removed for this exam" + U_RESET);
            waiting_time = false;
            using_cheatcode++;
        }
        else
            ui::plain(U_RED + "✘ Unknown command" + U_RESET + "  — type " + U_LIME + "help" + U_RESET + " for the list of commands");
    }
}

// ==> Starting a new exercise (does not enter the prompt loop)
bool exam::start_new_ex(void)
{
    load_settings();
    if (!backup)
    {
        list_ex_lvl = list_dir();
        exercise ex = randomize_exercise(list_ex_lvl, setting_dse);
        delete current_ex;
        current_ex = new exercise(ex);
        prepare_current_ex();
        store_data();
    }
    info();
    return (true);
}

int main(void)
{
    signal(SIGINT, sigc);
    signal(SIGQUIT, sigc);
    signal(SIGTERM, sigc);

    if (file_exists("a.out"))
        remove("a.out");
    ensure_dir(TOKEN_DIR);

    exam exm;
    exm.check_vip();

    if (!file_exists(".system/acceptCGV"))
        CGVAcceptation();

    if (file_exists(TOKEN_FILE))
        exm.restore_data();
    else
        exm.ask_param();

    exm.start_new_ex();
    exm.exam_prompt();
    return (0);
}
