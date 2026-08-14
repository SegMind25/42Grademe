#include "exam.hpp"

// ==> Animation of exercise name
void exam::exam_random_show(void)
{
    int pot_pts;
    if (level == 0)
        pot_pts = 0;
    else
        pot_pts = level_per_ex_save;
    std::map<int, exercise>::iterator it = list_ex_lvl.begin();
    std::cout << "    " << YELLOW << current_ex->get_assignement() << RESET << ": " << LIME << it->second.get_name() << RESET << " for " << pot_pts << " potential points (" << CYAN << "Current" << RESET << ")" << std::endl;
    double time = 100000;
    for (int i = 0; i < 20; i++)
    {
        std::cout << REMOVE_LINE;
        std::cout << "    " << YELLOW << current_ex->get_assignement() << RESET << ": " << LIME << it->second.get_name() << RESET << " for " << pot_pts << " potential points (" << CYAN << "Current" << RESET << ")" << std::endl;
        it++;
        if (it == list_ex_lvl.end())
            it = list_ex_lvl.begin();
        if (list_ex_lvl.size() == 1)
            break;
        usleep(time);
        time += 10000;
    }
    std::cout << REMOVE_LINE;
    std::cout << "    " << YELLOW << current_ex->get_assignement() << RESET << ": " << LIME << current_ex->get_name() << RESET << " for " << pot_pts << " potential points (" << CYAN << "Current" << RESET << ")" << std::endl;
    if (level_per_ex != 100)
    {
        for (int i = 0; i < level_per_ex_save && level == 0; i++)
        {
            std::cout << REMOVE_LINE;
            std::cout << "    " << YELLOW << current_ex->get_assignement() << RESET << ": " << LIME << current_ex->get_name() << RESET << " for " << i << " potential points (" << CYAN << "Current" << RESET << ")" << std::endl;
            usleep(40000);
        }
    }
    std::cout << REMOVE_LINE;
    std::cout << "    " << YELLOW << current_ex->get_assignement() << RESET << ": " << LIME << current_ex->get_name() << RESET << " for " << (int)level_per_ex_save << " potential points (" << CYAN << "Current" << RESET << ")" << std::endl;
}

// ==> Help section
void exam::exam_help(void)
{
    ui::frame_open("HELP", false);
    ui::blank();
    ui::line(U_DIM + "  ───  BASIC COMMANDS  ───" + U_RESET);
    ui::blank();
    ui::line("   " + U_YELLOW + "help" + U_RESET + "        " + U_WHITE + "display this help" + U_RESET);
    ui::line("   " + U_YELLOW + "status" + U_RESET + "      " + U_WHITE + "display information about the exam" + U_RESET);
    ui::line("   " + U_YELLOW + "grademe" + U_RESET + "     " + U_WHITE + "grade your exercise" + U_RESET);
    ui::line("   " + U_YELLOW + "finish" + U_RESET + "      " + U_WHITE + "exit the exam" + U_RESET);
    ui::line("   " + U_YELLOW + "settings" + U_RESET + "    " + U_WHITE + "display settings menu" + U_RESET);
    ui::line("   " + U_YELLOW + "sponsor" + U_RESET + "     " + U_WHITE + "visit sponsor page to become VIP" + U_RESET);
    ui::line("   " + U_YELLOW + "repo_git" + U_RESET + "    " + U_WHITE + "visit github repo" + U_RESET);
    ui::blank();
    ui::line(U_DIM + "  See the github repo to find some more 'cheat' commands." + U_RESET);
    ui::sep();
    ui::line(U_MAGENTA + U_BOLD + "  VIP MENU (sponsor or contribute):" + U_RESET);
    ui::blank();
    ui::line("   " + U_YELLOW + "force_success" + U_RESET + "     " + U_WHITE + "force an exercise to success" + U_RESET);
    ui::line("   " + U_YELLOW + "remove_grade_time" + U_RESET + " " + U_WHITE + "remove grade time limit between two grademe" + U_RESET);
    ui::line("   " + U_YELLOW + "gradenow" + U_RESET + "         " + U_WHITE + "instant grade exercise" + U_RESET);
    ui::line("   " + U_YELLOW + "new_ex" + U_RESET + "           " + U_WHITE + "generate a new exercise for the same level" + U_RESET);
    ui::blank();
    ui::frame_close();
}

// ==> Display one level history (failures + success)
static void show_level_ex(int failures, const std::string &name, bool current = false)
{
    for (int i = 0; i < failures; i++)
    {
        ui::line("      " + U_YELLOW + "[" + std::to_string(i) + "]" + U_RESET
                 + "  " + U_GRAY + name + U_RESET + "  " + U_RED + "✗  Failure" + U_RESET);
    }
    std::string tag = current ? std::string(U_CYAN) + "●  Current" : std::string(U_GREEN) + "✔  Success";
    ui::line("      " + U_YELLOW + "[" + std::to_string(failures) + "]" + U_RESET
             + "  " + U_WHITE + name + U_RESET + "  " + tag + U_RESET);
}

// ==> display of exam status
void exam::info(void)
{
    ui::frame_open("EXAM STATUS", false);
    ui::blank();
    std::string mode = reelmode ? std::string(U_MAGENTA) + "REAL" : std::string(U_YELLOW) + "TEST";
    ui::line("   " + U_DIM + "Mode" + U_RESET + "            " + mode + U_RESET
             + ui::pad(std::string(U_DIM) + "Grade" + U_RESET + "  " + U_WHITE + std::to_string(level_per_ex_save * level) + "/100" + U_RESET, 22)
             + U_DIM + "Level" + U_RESET + "  " + U_WHITE + std::to_string(level) + "/" + std::to_string(level_max) + U_RESET);
    ui::blank();
    ui::sep();
    ui::blank();
    for (std::map<int, exercise>::iterator it = lvl_ex.begin(); it != lvl_ex.end(); it++)
    {
        ui::line("  " + U_DIM + "LEVEL " + std::to_string(it->second.get_lvl()) + ":" + U_RESET);
        show_level_ex(it->second.get_assignement(), it->second.get_name());
        ui::blank();
    }
    ui::line("  " + U_DIM + "LEVEL " + std::to_string(level) + ":" + U_RESET);
    if (current_ex->get_assignement() == 0 && backup == 0 && !changex)
        exam_random_show();
    else
        show_level_ex(current_ex->get_assignement(), current_ex->get_name(), true);
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line("  " + U_DIM + "Current assignment" + U_RESET + "  " + U_WHITE + U_BOLD + current_ex->get_name() + U_RESET
             + "  for  " + U_LIME + U_BOLD + std::to_string((int)(((double)level + 1) / (double)level_max * 100)) + " xp" + U_RESET);
    ui::line("  " + U_DIM + "Attempt" + U_RESET + "  " + U_YELLOW + std::to_string(current_ex->get_assignement()) + U_RESET);
    ui::blank();
    ui::line("  " + U_DIM + "Subject location" + U_RESET + "  " + U_LIME + current_path() + "/subjects/subject.en.txt" + U_RESET);
    ui::line("  " + U_DIM + "Rendu location" + U_RESET + "  " + U_RED + current_path() + "/rendu/" + current_ex->get_name() + "/" + U_RESET);
    ui::line("  " + U_DIM + "Git needed" + U_RESET + "  " + U_GRAY + "No — you don't need git here." + U_RESET);
    ui::blank();
    {
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&end_time), "%d/%m/%Y %H:%M:%S");
        ui::line("  " + U_DIM + "End date" + U_RESET + "  " + U_LIME + oss.str() + U_RESET);
    }
    ui::line("  " + U_DIM + "Time left" + U_RESET + "  " + U_LIME + remaining_time(end_time) + U_RESET);
    ui::blank();
    ui::sep();
    ui::line_center("Use " + U_LIME + "grademe" + U_RESET + " to be graded, or " + U_LIME + "help" + U_RESET + " for help.", U_WHITE);
    ui::frame_close();
    backup = 1;
}

void exam::infovip(void)
{
    ui::frame_open("EXAM STATUS (VIP)", false);
    ui::blank();
    std::string mode = reelmode ? std::string(U_MAGENTA) + "REAL" : std::string(U_YELLOW) + "TEST";
    ui::line("   " + U_DIM + "Mode" + U_RESET + "            " + mode + U_RESET
             + ui::pad(std::string(U_DIM) + "Grade" + U_RESET + "  " + U_WHITE + std::to_string(level_per_ex_save * level) + "/100" + U_RESET, 22)
             + U_DIM + "Level" + U_RESET + "  " + U_WHITE + std::to_string(level) + "/" + std::to_string(level_max) + U_RESET);
    ui::blank();
    ui::sep();
    ui::blank();
    for (std::map<int, exercise>::iterator it = lvl_ex.begin(); it != lvl_ex.end(); it++)
    {
        ui::line("  " + U_DIM + "LEVEL " + std::to_string(it->second.get_lvl()) + ":" + U_RESET);
        show_level_ex(it->second.get_assignement(), it->second.get_name());
        ui::blank();
    }
    ui::line("  " + U_DIM + "LEVEL " + std::to_string(level) + ":" + U_RESET);
    if (current_ex->get_assignement() == 0 && backup == 0 && !changex)
        exam_random_show();
    else
        show_level_ex(current_ex->get_assignement(), current_ex->get_name(), true);
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line("  " + U_DIM + "Current assignment" + U_RESET + "  " + U_WHITE + U_BOLD + current_ex->get_name() + U_RESET
             + "  for  " + U_LIME + U_BOLD + std::to_string((int)(((double)level + 1) / (double)level_max * 100)) + " xp" + U_RESET);
    ui::line("  " + U_DIM + "Attempt" + U_RESET + "  " + U_YELLOW + std::to_string(current_ex->get_assignement()) + U_RESET);
    ui::blank();
    ui::line("  " + U_DIM + "Subject location" + U_RESET + "  " + U_LIME + current_path() + "/subjects/subject.en.txt" + U_RESET);
    ui::line("  " + U_DIM + "Rendu location" + U_RESET + "  " + U_RED + current_path() + "/rendu/" + current_ex->get_name() + "/" + U_RESET);
    ui::line("  " + U_DIM + "Git needed" + U_RESET + "  " + U_GRAY + "No — you don't need git here." + U_RESET);
    ui::blank();
    {
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&end_time), "%d/%m/%Y %H:%M:%S");
        ui::line("  " + U_DIM + "End date" + U_RESET + "  " + U_LIME + oss.str() + U_RESET);
    }
    ui::line("  " + U_DIM + "Time left" + U_RESET + "  " + U_LIME + remaining_time(end_time) + U_RESET);
    ui::blank();
    ui::sep();
    ui::line_center("Use " + U_LIME + "grademe" + U_RESET + " to be graded, or " + U_LIME + "help" + U_RESET + " for help.", U_WHITE);
    ui::frame_close();
}

// ==> display connexion animation
void connexion(void)
{
    ui::clear();
    std::cout << U_CYAN;
    std::string examsystem = "examshell";
    for (int i = 0; i < (int)examsystem.length(); i++)
    {
        std::cout << examsystem[i];
        usleep(70000);
        fflush(stdout);
    }
    std::cout << U_RESET << std::endl;
    usleep(600000);
    ui::frame_open("CONNEXION", true);
    ui::blank();
    ui::line("  " + U_DIM + "Connecting to exam server..." + U_RESET);
    ui::blank();
    ui::line("   " + U_DIM + "login:" + U_RESET + "  " + U_WHITE + U_BOLD + std::string(getenv("USER") ? getenv("USER") : "unknown") + U_RESET);
    ui::line("   " + U_DIM + "password:" + U_RESET + "  " + U_MAGENTA + U_BOLD + "••••••••••" + U_RESET);
    ui::blank();
    ui::line("   " + U_LIME + "✔  Authentication successful" + U_RESET);
    ui::blank();
    ui::frame_close();
    usleep(700000);
}

// ==> First menu display
int exam::stud_or_swim(void)
{
    std::string choice = "-2";
    while (choice == "-1" || choice == "-2")
    {
        ui::frame_open("MAIN MENU", true);
        ui::blank();
        if (vip)
            ui::line_center(U_GOLD + U_BOLD + "★  VIP MEMBER  ★" + U_RESET, U_WHITE);
        else
            ui::line_center(U_DIM + "Made by " + U_LIME + "jcluzet" + U_RESET + U_DIM + "  ·  free and open-source" + U_RESET, U_WHITE);
        ui::blank();
        ui::card(1, "PISCINE PART", "Train for the piscine (exam weeks 01-04)");
        ui::blank();
        ui::card(2, "STUDENT PART", "Train for the student exams (ranks 02-06)");
        ui::blank();
        ui::card(3, "SETTINGS", "Tweak the exam experience");
        ui::blank();
        ui::frame_close();
        choice = ui::ask("Enter your choice [1-3]");
        if (choice == "3")
        {
            settings_menu();
            choice = "-2";
        }
        else if (choice != "1" && choice != "2")
            choice = "-1";
    }
    return (atoi(choice.c_str()));
}

// ==> Setting MENU
void exam::settings_menu(void)
{
    load_settings();
    char *logname = std::getenv("LOGNAME");
    char *lognameexam;
    std::string input = "";
    while (input != "0")
    {
        lognameexam = std::getenv("LOGNAMELOG42EXAM");
        if (!lognameexam)
            lognameexam = (char *)"unknown";
        if (!logname)
            logname = (char *)"unknown";
        ui::frame_open("SETTINGS", false);
        ui::blank();
        ui::line("   " + U_RED + "0" + U_RESET + "   " + U_DIM + "Back" + U_RESET);
        ui::sep();
        ui::blank();
        ui::line("   " + U_YELLOW + "1" + U_RESET + "   " + U_WHITE + U_BOLD + "Enable exercises you already passed" + U_RESET
                 + (setting_dse ? ui::badge("ON", U_GREEN) : ui::badge("OFF", U_RED)));
        ui::blank();
        ui::line("   " + U_YELLOW + "2" + U_RESET + "   " + U_WHITE + U_BOLD + "Enable cheat commands" + U_RESET
                 + (setting_dcc ? ui::badge("ON", U_GREEN) : ui::badge("OFF", U_RED)));
        ui::blank();
        ui::line("   " + U_YELLOW + "3" + U_RESET + "   " + U_WHITE + U_BOLD + "Anonymise data sending to LOG" + U_RESET
                 + (setting_an ? ui::badge("ON", U_GREEN) : ui::badge("OFF", U_RED)));
        ui::line("       " + U_DIM + "> Name sent to log is currently: " + U_WHITE + std::string(lognameexam) + U_RESET);
        ui::blank();
        ui::frame_close();
        input = ui::ask("Enter your choice [0-3]");
        if (input == "1")
            setting_dse = !setting_dse;
        else if (input == "2")
            setting_dcc = !setting_dcc;
        else if (input == "3")
        {
            setting_an = !setting_an;
            if (setting_an)
                setenv("LOGNAMELOG42EXAM", generate_unique_id().c_str(), 1);
            else
                setenv("LOGNAMELOG42EXAM", logname, 1);
        }
    }
    std::cout << REMOVE_LINE << U_WHITE << U_BOLD << "  Saving settings..." << U_RESET << std::endl;
    std::string tmp = "bash .system/data_sender.sh \"settings_out:enable_ead>" + std::to_string(setting_dse);
    tmp += "__settings:enable_cheat>" + std::to_string(setting_dcc) + "\"";
    system(tmp.c_str());
    save_settings();
}

// ==> Display the menu for the student part
int exam::stud_menu(void)
{
    std::string choice = "-2";
    while (choice == "-1" || choice == "-2")
    {
        ui::frame_open("STUDENT PART", false);
        ui::blank();
        ui::card(2, "EXAM RANK 02", "Functions & basic algorithms");
        ui::blank();
        ui::card(3, "EXAM RANK 03", "Intermediate algorithms");
        ui::blank();
        ui::card(4, "EXAM RANK 04", "Data structures & memory");
        ui::blank();
        ui::card(5, "EXAM RANK 05", "Advanced algorithms");
        ui::blank();
        ui::card(6, "EXAM RANK 06", "The final boss");
        ui::blank();
        ui::line("   " + U_RED + "0" + U_RESET + "   " + U_DIM + "Back to menu" + U_RESET);
        ui::blank();
        ui::frame_close();
        choice = ui::ask("Enter your choice [2-6]");
        if (choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "0")
            choice = "-1";
    }
    return (atoi(choice.c_str()));
}

// ==> Display the menu for the piscine part
int exam::piscine_menu(void)
{
    std::string choice = "-2";
    while (choice == "-1" || choice == "-2")
    {
        ui::frame_open("PISCINE PART", false);
        ui::blank();
        ui::card(1, "EXAM WEEK 01", "Easy warm-up exercises");
        ui::blank();
        ui::card(2, "EXAM WEEK 02", "Getting comfortable");
        ui::blank();
        ui::card(3, "EXAM WEEK 03", "Easy / Medium collection");
        ui::blank();
        ui::card(4, "EXAM WEEK 04", "Medium / Hard collection");
        ui::blank();
        ui::line("   " + U_RED + "0" + U_RESET + "   " + U_DIM + "Back to menu" + U_RESET);
        ui::blank();
        ui::frame_close();
        choice = ui::ask("Enter your choice [1-4]");
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "0")
            choice = "-1";
    }
    return (atoi(choice.c_str()));
}
