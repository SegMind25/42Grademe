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
            ui::line_center(U_DIM + "Made by " + U_LIME + "Bekkali - SegMind25" + U_RESET + U_DIM + "  ·  free and open-source" + U_RESET, U_WHITE);
        ui::blank();
        ui::card(1, "PISCINE PART", "Train for the piscine (exam weeks 01-04)");
        ui::blank();
        ui::card(2, "STUDENT PART", "Train for the student exams (ranks 02-06)");
        ui::blank();
        ui::card(3, "BACKTRACKING", "Problem solving with backtracking");
        ui::blank();
        ui::card(4, "SETTINGS", "Tweak the exam experience");
        ui::blank();
        ui::frame_close();
        choice = ui::ask("Enter your choice [1-4]");
        if (choice == "4")
        {
            settings_menu();
            choice = "-2";
        }
        else if (choice == "3")
        {
            backtracking_menu();
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

// ==> Display the backtracking problem solving section
void exam::backtracking_menu(void)
{
    ui::frame_open("BACKTRACKING PROBLEM SOLVING", true);
    ui::blank();
    ui::line_center(U_YELLOW + U_BOLD + "What is Backtracking?" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("  " + U_WHITE + "Backtracking is a general algorithmic technique for solving");
    ui::line("  problems recursively by trying to build a solution incrementally,");
    ui::line("  one piece at a time, removing those solutions that fail to satisfy");
    ui::line("  the constraints of the problem at any point in time." + U_RESET);
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line_center(U_YELLOW + U_BOLD + "How to Solve Backtracking Problems" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("  " + U_CYAN + "1." + U_RESET + "  " + U_WHITE + "Define the state space:" + U_RESET + " Understand what a partial solution looks like.");
    ui::line("  " + U_CYAN + "2." + U_RESET + "  " + U_WHITE + "Choose the next step:" + U_RESET + " Decide which decision to make next.");
    ui::line("  " + U_CYAN + "3." + U_RESET + "  " + U_WHITE + "Check constraints:" + U_RESET + " If the current path violates any rule, stop.");
    ui::line("  " + U_CYAN + "4." + U_RESET + "  " + U_WHITE + "Check if solution is complete:" + U_RESET + " If yes, record or return it.");
    ui::line("  " + U_CYAN + "5." + U_RESET + "  " + U_WHITE + "Recurse:" + U_RESET + " Try the next possible choice and repeat.");
    ui::line("  " + U_CYAN + "6." + U_RESET + "  " + U_WHITE + "Undo (backtrack):" + U_RESET + " Revert the last decision and try another path.");
    ui::blank();
    ui::line("  " + U_DIM + "Common pattern:" + U_RESET + "  " + U_LIME + "for each choice:" + U_RESET);
    ui::line("      " + U_LIME + "if" + U_RESET + " (valid(choice))      " + U_DIM + "// constraint check" + U_RESET);
    ui::line("          make(choice);       " + U_DIM + "// apply" + U_RESET);
    ui::line("          backtrack(state);    " + U_DIM + "// recurse" + U_RESET);
    ui::line("          undo(choice);        " + U_DIM + "// revert" + U_RESET);
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line_center(U_MAGENTA + U_BOLD + "Choose a problem to solve:" + U_RESET, U_WHITE);
    ui::blank();
    ui::card(1, "N-QUEENS", "Place N queens on NxN board safely");
    ui::blank();
    ui::card(2, "SUDOKU SOLVER", "Fill a 9x9 grid following Sudoku rules");
    ui::blank();
    ui::card(3, "RAT IN A MAZE", "Find path from start to end in a maze");
    ui::blank();
    ui::line("   " + U_RED + "0" + U_RESET + "   " + U_DIM + "Back to main menu" + U_RESET);
    ui::blank();
    ui::frame_close();
    std::string choice = ui::ask("Enter the problem number [1-3]");
    if (choice == "0")
        return;

    std::string ex_name;
    int ex_level = 0;
    if (choice == "1") { ex_name = "nqueens"; ex_level = 0; }
    else if (choice == "2") { ex_name = "sudoku"; ex_level = 0; }
    else if (choice == "3") { ex_name = "maze"; ex_level = 0; }
    else return;

    std::string path = ".subjects/BACKTRACKING/" + std::to_string(ex_level) + "/" + ex_name + "/";

    system("mkdir rendu 2> /dev/null");
    system("mkdir subjects 2> /dev/null");
    system("mkdir .system/grading 2> /dev/null");
    system(("cp -r " + path + "attachment/* subjects/").c_str());
    system(("cp " + path + "* .system/grading/ >/dev/null 2>&1").c_str());
    system(("mkdir rendu/" + ex_name + " 2> /dev/null").c_str());

    ui::clear();
    ui::frame_open("BACKTRACKING: " + ex_name, false);
    ui::blank();
    std::ifstream subj("subjects/subject.en.txt");
    std::string line;
    while (std::getline(subj, line))
        ui::line("  " + U_WHITE + line + U_RESET);
    subj.close();
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line("  " + U_DIM + "Put your solution in:" + U_RESET + "  " + U_LIME + current_path() + "/rendu/" + ex_name + "/" + U_RESET);
    ui::line("  " + U_DIM + "Then type" + U_RESET + "  " + U_LIME + "grademe" + U_RESET + "  " + U_DIM + "to be graded." + U_RESET);
    ui::blank();
    ui::frame_close();

    while (1)
    {
        char *rline = readline("\e[96m┌─\e[0m\e[93m backtracking \e[0m\e[96m─\e[0m\e[97m›\e[0m ");
        if (!rline) break;
        std::string input = rline;
        free(rline);
        while (!input.empty() && input.back() == ' ') input.pop_back();
        while (!input.empty() && input.front() == ' ') input.erase(input.begin());
        if (input.empty()) continue;
        add_history(input.c_str());
        if (input == "grademe")
        {
            system("bash .system/grading/tester.sh");
            if (file_exists(".system/grading/passed"))
            {
                ui::clear();
                ui::frame_open("SUCCESS", false);
                ui::blank();
                ui::line_center(U_GREEN + U_BOLD + "✔  ALL TESTS PASSED  ✔" + U_RESET, U_WHITE);
                ui::blank();
                ui::line("   " + U_DIM + "Exercise" + U_RESET + "  " + U_WHITE + U_BOLD + ex_name + U_RESET);
                ui::blank();
                ui::frame_close();
                system("rm -f .system/grading/passed");
                ui::press_enter("Press Enter to continue...");
                break;
            }
            else
            {
                ui::clear();
                ui::frame_open("FAILURE", false);
                ui::blank();
                ui::line_center(U_RED + U_BOLD + "✘  TESTS FAILED  ✘" + U_RESET, U_WHITE);
                ui::blank();
                if (file_exists("traceback"))
                {
                    std::ifstream tb("traceback");
                    std::string tline;
                    while (std::getline(tb, tline))
                        ui::line("  " + U_RED + tline + U_RESET);
                    tb.close();
                    system("rm -f traceback");
                }
                ui::blank();
                ui::frame_close();
                ui::press_enter("Press Enter to try again...");
                ui::clear();
                ui::frame_open("BACKTRACKING: " + ex_name, false);
                ui::blank();
                ui::line("  " + U_DIM + "Put your solution in:" + U_RESET + "  " + U_LIME + current_path() + "/rendu/" + ex_name + "/" + U_RESET);
                ui::line("  " + U_DIM + "Then type" + U_RESET + "  " + U_LIME + "grademe" + U_RESET + "  " + U_DIM + "to be graded." + U_RESET);
                ui::blank();
                ui::frame_close();
            }
        }
        else if (input == "subject" || input == "status")
        {
            ui::clear();
            ui::frame_open("SUBJECT: " + ex_name, false);
            ui::blank();
            std::ifstream subj2("subjects/subject.en.txt");
            std::string sl;
            while (std::getline(subj2, sl))
                ui::line("  " + U_WHITE + sl + U_RESET);
            subj2.close();
            ui::blank();
            ui::frame_close();
        }
        else if (input == "help")
        {
            ui::clear();
            ui::frame_open("HELP", false);
            ui::blank();
            ui::line("   " + U_YELLOW + "grademe" + U_RESET + "     " + U_WHITE + "grade your exercise" + U_RESET);
            ui::line("   " + U_YELLOW + "subject" + U_RESET + "      " + U_WHITE + "display the subject" + U_RESET);
            ui::line("   " + U_YELLOW + "finish" + U_RESET + "       " + U_WHITE + "go back to main menu" + U_RESET);
            ui::blank();
            ui::frame_close();
        }
        else if (input == "finish" || input == "exit" || input == "quit")
            break;
        else
            ui::plain(U_RED + "  Unknown command. Type " + U_LIME + "help" + U_RESET + U_RED + " for help." + U_RESET);
    }
}
