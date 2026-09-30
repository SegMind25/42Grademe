#include "exam.hpp"

// ==> Animation of exercise name (rolls through the level's exercises)
void exam::exam_random_show(void)
{
    std::string idx = "      " + U_YELLOW + "[" + std::to_string(current_ex->get_assignement()) + "]" + U_RESET + "  ";
    auto row = [&](const std::string &name, int pts) {
        // truncated: a wrapped row would break the REMOVE_LINE animation
        return (ui::truncate(idx + U_WHITE + name + U_RESET + "  " + U_CYAN + "●  Current" + U_RESET
                + U_DIM + "  (" + std::to_string(pts) + " pts)" + U_RESET, ui::text_width()));
    };
    ui::line(row(current_ex->get_name(), level_per_ex_save));
    if (list_ex_lvl.size() > 1)
    {
        std::map<int, exercise>::iterator it = list_ex_lvl.begin();
        useconds_t delay = 60000;
        for (int i = 0; i < 18; i++)
        {
            std::cout << REMOVE_LINE;
            ui::line(row(it->second.get_name(), level_per_ex_save));
            std::cout.flush();
            if (++it == list_ex_lvl.end())
                it = list_ex_lvl.begin();
            usleep(delay);
            delay += 8000;
        }
    }
    std::cout << REMOVE_LINE;
    ui::line(row(current_ex->get_name(), level_per_ex_save));
}

// ==> Help section
void exam::exam_help(void)
{
    auto cmd = [](const std::string &name, const std::string &desc) {
        ui::line("   " + U_YELLOW + ui::pad(name, 18) + U_RESET + U_WHITE + desc + U_RESET);
    };
    ui::frame_open("HELP", false);
    ui::blank();
    ui::line("  " + U_CYAN + U_BOLD + "COMMANDS" + U_RESET);
    cmd("help", "display this help");
    cmd("status", "display information about the exam");
    cmd("grademe", "grade your exercise");
    cmd("settings", "display settings menu");
    cmd("finish", "exit the exam (progress is lost)");
    cmd("sponsor", "support the project / become VIP");
    cmd("repo_git", "open the github repo");
    ui::blank();
    ui::line("  " + U_ORANGE + U_BOLD + "CHEAT COMMANDS" + U_RESET + U_DIM + "  (enable them in settings)" + U_RESET
             + "  " + (setting_dcc ? ui::badge("ON", U_GREEN) : ui::badge("OFF", U_RED)));
    cmd("new_ex", "draw a new exercise for the same level");
    cmd("remove_grade_time", "remove waiting time between two grademe");
    ui::blank();
    ui::line("  " + U_MAGENTA + U_BOLD + "VIP COMMANDS" + U_RESET + U_DIM + "  (sponsor or contribute)" + U_RESET
             + "  " + (vip ? ui::badge("ACTIVE", U_GREEN) : ui::badge("LOCKED", U_GRAY)));
    cmd("gradenow", "instant grading, no waiting animation");
    cmd("force_success", "force the current exercise to success");
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
    ui::frame_open(vip ? "EXAM STATUS  ★ VIP" : "EXAM STATUS", false);
    ui::blank();
    std::string mode = reelmode ? std::string(U_MAGENTA) + U_BOLD + "REAL" : std::string(U_YELLOW) + U_BOLD + "TEST";
    std::string exam_label = (student ? "Exam Rank 0" : "Exam Week 0") + std::to_string(exam_number);
    ui::line("   " + U_DIM + "Exam " + U_RESET + "  " + U_WHITE + U_BOLD + exam_label + U_RESET + "   " + mode + U_RESET);
    ui::line("   " + U_DIM + "Grade" + U_RESET + "  " + ui::progress(grade(), 20) + "  " + U_WHITE + U_BOLD + std::to_string(grade()) + "/100" + U_RESET
             + U_DIM + "   Level " + U_RESET + U_WHITE + std::to_string(level) + "/" + std::to_string(level_max) + U_RESET);
    ui::blank();
    ui::sep();
    ui::blank();
    for (std::map<int, exercise>::iterator it = lvl_ex.begin(); it != lvl_ex.end(); it++)
    {
        ui::line("  " + U_DIM + "LEVEL " + std::to_string(it->second.get_lvl()) + U_RESET);
        show_level_ex(it->second.get_assignement(), it->second.get_name());
    }
    ui::line("  " + U_DIM + "LEVEL " + std::to_string(level) + U_RESET);
    if (current_ex->get_assignement() == 0 && !backup && !changex)
        exam_random_show();
    else
        show_level_ex(current_ex->get_assignement(), current_ex->get_name(), true);
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line("  " + U_DIM + "Assignment " + U_RESET + "  " + U_WHITE + U_BOLD + current_ex->get_name() + U_RESET
             + U_DIM + "  ·  " + U_RESET + U_LIME + std::to_string(level_per_ex_save) + " pts" + U_RESET
             + U_DIM + "  ·  attempt " + U_RESET + U_YELLOW + std::to_string(current_ex->get_assignement()) + U_RESET);
    {
        int max_p = ui::text_width() - 16;
        std::string subj = current_path() + "/subjects/subject.en.txt";
        std::string rendu = current_path() + "/rendu/" + current_ex->get_name() + "/";
        ui::line("  " + U_DIM + "Subject    " + U_RESET + "  " + U_LIME + ui::truncate(subj, max_p) + U_RESET);
        ui::line("  " + U_DIM + "Rendu      " + U_RESET + "  " + U_RED + ui::truncate(rendu, max_p) + U_RESET);
    }
    ui::blank();
    {
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&end_time), "%d/%m/%Y %H:%M");
        ui::line("  " + U_DIM + "Ends at    " + U_RESET + "  " + U_WHITE + oss.str() + U_RESET
                 + U_DIM + "  ·  left " + U_RESET + U_LIME + U_BOLD + remaining_time(end_time) + U_RESET);
    }
    ui::line("  " + U_DIM + "Git        " + U_RESET + "  " + U_GRAY + "not needed here (you will need it in the real exam)" + U_RESET);
    ui::blank();
    ui::sep();
    ui::line_center("Type " + U_LIME + "grademe" + U_RESET + " to be graded, " + U_LIME + "status" + U_RESET + " to refresh, or " + U_LIME + "help" + U_RESET + ".", U_WHITE);
    ui::frame_close();
    backup = 1;
}

// ==> display connexion animation
void connexion(void)
{
    ui::clear();
    std::cout << "\n  " << U_CYAN << U_BOLD;
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
        if (vip)
            ui::line_center(U_GOLD + U_BOLD + "★  VIP MEMBER  ★" + U_RESET, U_WHITE);
        else
            ui::line_center(U_DIM + "Made by " + U_LIME + "Bekkali - SegMind25" + U_RESET + U_DIM + "  ·  free and open-source" + U_RESET, U_WHITE);
        ui::blank();
        ui::card(1, "PISCINE PART", "Train for the piscine (exam weeks 01-04)");
        ui::card(2, "STUDENT PART", "Train for the student exams (ranks 02-06)");
        ui::card(3, "BACKTRACKING", "Problem solving with backtracking");
        ui::card(4, "SETTINGS", "Tweak the exam experience");
        ui::blank();
        ui::line("   " + U_RED + U_BOLD + "0" + U_RESET + "   " + U_DIM + "Quit" + U_RESET);
        ui::frame_close();
        choice = ui::ask("Enter your choice [1-4, 0 to quit]");
        if (choice == "0")
        {
            ui::clear();
            ui::plain(U_LIME + "See you soon, good luck for your exam! 🍀" + U_RESET);
            exit(0);
        }
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
        if (!lognameexam || !*lognameexam)
            lognameexam = (char *)username.c_str();
        if (!logname || !*logname)
            logname = (char *)username.c_str();
        auto opt = [](const std::string &num, const std::string &label, bool on) {
            std::string state = on ? std::string(U_GREEN) + U_BOLD + "● ON " : std::string(U_GRAY) + "○ OFF";
            ui::line("   " + U_YELLOW + U_BOLD + num + U_RESET + "   " + state + U_RESET + "   " + U_WHITE + label + U_RESET);
        };
        ui::frame_open("SETTINGS", false);
        ui::blank();
        opt("1", "Enable exercises you already passed", setting_dse);
        opt("2", "Enable cheat commands", setting_dcc);
        opt("3", "Anonymise data sent to the log", setting_an);
        ui::line("               " + U_DIM + "name sent: " + U_RESET + U_WHITE + std::string(lognameexam) + U_RESET);
        ui::blank();
        ui::sep();
        ui::line("   " + U_RED + U_BOLD + "0" + U_RESET + "   " + U_DIM + "Save & go back" + U_RESET);
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
    save_settings();
    ui::plain(U_LIME + "✔  Settings saved" + U_RESET);
    send_data("settings_out:enable_ead>" + std::to_string(setting_dse) + "__settings:enable_cheat>" + std::to_string(setting_dcc));
}

// ==> Display the menu for the student part
int exam::stud_menu(void)
{
    std::string choice = "-2";
    while (choice == "-1" || choice == "-2")
    {
        ui::frame_open("STUDENT PART", false);
        ui::card(2, "EXAM RANK 02", "Functions & basic algorithms");
        ui::card(3, "EXAM RANK 03", "Intermediate algorithms");
        ui::card(4, "EXAM RANK 04", "Data structures & memory");
        ui::card(5, "EXAM RANK 05", "Advanced algorithms");
        ui::card(6, "EXAM RANK 06", "The final boss");
        ui::blank();
        ui::line("   " + U_RED + U_BOLD + "0" + U_RESET + "   " + U_DIM + "Back to menu" + U_RESET);
        ui::frame_close();
        choice = ui::ask("Enter your choice [2-6, 0 to go back]");
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
        ui::card(1, "EXAM WEEK 01", "Easy warm-up exercises");
        ui::card(2, "EXAM WEEK 02", "Getting comfortable");
        ui::card(3, "EXAM WEEK 03", "Easy / Medium collection");
        ui::card(4, "EXAM WEEK 04", "Medium / Hard collection");
        ui::blank();
        ui::line("   " + U_RED + U_BOLD + "0" + U_RESET + "   " + U_DIM + "Back to menu" + U_RESET);
        ui::frame_close();
        choice = ui::ask("Enter your choice [1-4, 0 to go back]");
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "0")
            choice = "-1";
    }
    return (atoi(choice.c_str()));
}

// ==> Print a text file inside the current frame
static void show_file(const std::string &path)
{
    std::ifstream f(path.c_str());
    std::string l;
    while (std::getline(f, l))
        ui::line("  " + U_WHITE + l + U_RESET);
}

static void backtracking_hint(const std::string &ex_name)
{
    ui::line("  " + U_DIM + "Put your solution in" + U_RESET + "  " + U_LIME + ui::truncate(current_path() + "/rendu/" + ex_name + "/" + ex_name + ".c", ui::text_width() - 24) + U_RESET);
    ui::line("  " + U_DIM + "Then type" + U_RESET + "  " + U_LIME + "grademe" + U_RESET + U_DIM + "  ·  " + U_RESET + U_LIME + "subject" + U_RESET + U_DIM + "  ·  " + U_RESET + U_LIME + "help" + U_RESET + U_DIM + "  ·  " + U_RESET + U_LIME + "finish" + U_RESET);
}

// ==> Display the backtracking problem solving section
void exam::backtracking_menu(void)
{
    static const char *names[] = {"nqueens", "sudoku", "maze", "wordsearch", "subsetsum"};
    static const int levels[] = {0, 0, 0, 1, 1};
    std::string choice;
    while (true)
    {
        ui::frame_open("BACKTRACKING PROBLEM SOLVING", false);
        ui::blank();
        ui::line("  " + U_YELLOW + U_BOLD + "What is backtracking?" + U_RESET);
        ui::line("  A technique for solving problems by building solutions incrementally, and backtracking as soon as a constraint is violated.");
        ui::blank();
        ui::line("  " + U_YELLOW + U_BOLD + "How to solve" + U_RESET);
        ui::line("  " + U_CYAN + "1." + U_RESET + " Define the state   " + U_CYAN + "2." + U_RESET + " Choose next step   " + U_CYAN + "3." + U_RESET + " Check constraints");
        ui::line("  " + U_CYAN + "4." + U_RESET + " Complete? stop     " + U_CYAN + "5." + U_RESET + " Recurse            " + U_CYAN + "6." + U_RESET + " Undo (backtrack)");
        ui::sep();
        ui::line_center(U_MAGENTA + U_BOLD + "Choose a problem to solve" + U_RESET, U_WHITE);
        ui::card(1, "N-QUEENS", "Place N queens on an NxN board safely");
        ui::card(2, "SUDOKU SOLVER", "Fill a 9x9 grid following Sudoku rules");
        ui::card(3, "RAT IN A MAZE", "Find a path from start to end");
        ui::card(4, "WORDSEARCH", "Find all words in a grid (level 1)");
        ui::card(5, "SUBSET SUM", "Find subsets summing to a target (level 1)");
        ui::blank();
        ui::line("   " + U_RED + U_BOLD + "0" + U_RESET + "   " + U_DIM + "Back to main menu" + U_RESET);
        ui::frame_close();
        choice = ui::ask("Enter the problem number [1-5, 0 to go back]");
        if (choice == "0")
            return;
        if (choice.size() == 1 && choice[0] >= '1' && choice[0] <= '5')
            break;
    }

    int idx = choice[0] - '1';
    std::string ex_name = names[idx];
    std::string path = ".subjects/BACKTRACKING/" + std::to_string(levels[idx]) + "/" + ex_name + "/";

    system("rm -rf subjects .system/grading traceback");
    ensure_dir("rendu");
    ensure_dir("subjects");
    ensure_dir(".system/grading");
    ensure_dir("rendu/" + ex_name);
    system(("cp -r " + path + "attachment/* subjects/ 2>/dev/null").c_str());
    system(("cp " + path + "* .system/grading/ >/dev/null 2>&1").c_str());

    ui::frame_open("BACKTRACKING · " + ex_name, false);
    ui::blank();
    show_file("subjects/subject.en.txt");
    ui::blank();
    ui::sep();
    backtracking_hint(ex_name);
    ui::frame_close();

    while (1)
    {
        char *rline = readline("\033[96m┌─\033[0m\033[93m backtracking \033[0m\033[96m─\033[0m\033[97m›\033[0m ");
        if (!rline)
            break;
        std::string input = rline;
        free(rline);
        size_t b = input.find_first_not_of(" \t");
        input = (b == std::string::npos) ? "" : input.substr(b, input.find_last_not_of(" \t") - b + 1);
        if (input.empty())
            continue;
        add_history(input.c_str());
        if (input == "grademe")
        {
            remove(".system/grading/passed");
            remove("traceback");
            system("bash .system/grading/tester.sh");
            if (file_exists(".system/grading/passed"))
            {
                remove(".system/grading/passed");
                ui::frame_open("SUCCESS", false);
                ui::blank();
                ui::line_center(U_GREEN + U_BOLD + "✔  ALL TESTS PASSED  ✔" + U_RESET, U_WHITE);
                ui::blank();
                ui::line_center(U_DIM + "Exercise " + U_RESET + U_WHITE + U_BOLD + ex_name + U_RESET, U_WHITE);
                ui::blank();
                ui::frame_close();
                ui::press_enter("Press Enter to go back to the menu...");
                break;
            }
            ui::frame_open("FAILURE", false);
            ui::blank();
            ui::line_center(U_RED + U_BOLD + "✘  TESTS FAILED  ✘" + U_RESET, U_WHITE);
            ui::blank();
            if (file_exists("traceback"))
            {
                std::ifstream tb("traceback");
                std::string tline;
                while (std::getline(tb, tline))
                    ui::line("  " + tline);
                remove("traceback");
            }
            ui::blank();
            ui::sep();
            backtracking_hint(ex_name);
            ui::frame_close();
        }
        else if (input == "subject" || input == "status")
        {
            ui::frame_open("SUBJECT · " + ex_name, false);
            ui::blank();
            show_file("subjects/subject.en.txt");
            ui::blank();
            ui::sep();
            backtracking_hint(ex_name);
            ui::frame_close();
        }
        else if (input == "help")
        {
            ui::frame_open("HELP", false);
            ui::blank();
            ui::line("   " + U_YELLOW + "grademe" + U_RESET + "     " + U_WHITE + "grade your exercise" + U_RESET);
            ui::line("   " + U_YELLOW + "subject" + U_RESET + "     " + U_WHITE + "display the subject" + U_RESET);
            ui::line("   " + U_YELLOW + "finish" + U_RESET + "      " + U_WHITE + "go back to main menu" + U_RESET);
            ui::blank();
            ui::frame_close();
        }
        else if (input == "finish" || input == "exit" || input == "quit")
            break;
        else
            ui::plain(U_RED + "✘ Unknown command" + U_RESET + "  — type " + U_LIME + "help" + U_RESET + " for help");
    }
}
