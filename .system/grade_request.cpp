#include "exam.hpp"

// ==> Current grade out of 100
int exam::grade(void)
{
    if (level >= level_max)
        return (100);
    return (level * 100 / level_max);
}

void exam::fail_ex()
{
    send_data("fail_ex:" + current_ex->get_name() + " level:" + std::to_string(level) + " assignement:" + std::to_string(current_ex->get_assignement()));
    current_ex->up_assignement();
    current_ex->set_time_bef_grade(time(NULL) + current_ex->grade_time() * 60);
    store_data();
}

void exam::success_ex(bool force)
{
    // insert current_ex in lvl_ex
    lvl_ex.insert(std::pair<int, exercise>(current_ex->get_lvl(), *current_ex));
    // insert the success exercise into file .system/exam_token/success_ex
    if (!force)
    {
        ensure_dir("success");
        std::ofstream file("success/success_ex", std::ios::app);
        file << current_ex->get_name() << std::endl;
    }
    ui::clear();
    std::string title = force ? "FORCED SUCCESS" : "EXERCISE PASSED";
    ui::frame_open(title, false);
    ui::blank();
    ui::line_center(U_GREEN + U_BOLD + "✔  SUCCESS  ✔" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("   " + U_DIM + "Assignment" + U_RESET + "  " + U_WHITE + U_BOLD + current_ex->get_name() + U_RESET);
    ui::line("   " + U_DIM + "Level" + U_RESET + "       " + U_WHITE + U_BOLD + std::to_string(level) + U_RESET);
    ui::line("   " + U_DIM + "XP gained" + U_RESET + "   " + U_LIME + U_BOLD + std::to_string((int)level_per_ex_save) + " xp" + U_RESET);
    up_lvl();
    ui::blank();
    ui::line("   " + U_DIM + "Progress" + U_RESET + "    " + ui::progress(grade(), 24) + "  " + U_WHITE + U_BOLD + std::to_string(grade()) + "/100" + U_RESET);
    ui::blank();
    ui::frame_close();
    send_data(std::string(force ? "cheat_success_ex: " : "success_ex: ") + current_ex->get_name() + " level:" + std::to_string(level - 1) + " assignment:" + std::to_string(current_ex->get_assignement()));
    ui::press_enter(level >= level_max ? "Press Enter to see your results..." : "Press Enter for the next exercise...");
    level_per_ex += level_per_ex_save;
    changex = 0;
    backup = 0;
    if (!force && file_exists("rendu"))
    {
        ensure_dir("success");
        system("cp -r rendu/* success/ 2> /dev/null");
    }
    if (level >= level_max)
        end_exam();
    start_new_ex();
}

// ==> The exam time ran out
void exam::time_over(void)
{
    remove(TOKEN_FILE);
    send_data((student ? "exam_timeout: examrank0" : "exam_timeout: examweek0") + std::to_string(exam_number));
    ui::frame_open("TIME IS OVER", false);
    ui::blank();
    ui::line_center(U_RED + U_BOLD + "⏰  The exam time is over  ⏰" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("   " + U_DIM + "Exam" + U_RESET + "        " + U_WHITE + U_BOLD + (student ? "Exam Rank 0" : "Exam Week 0") + std::to_string(exam_number) + U_RESET);
    ui::line("   " + U_DIM + "Level" + U_RESET + "       " + U_WHITE + U_BOLD + std::to_string(level) + "/" + std::to_string(level_max) + U_RESET);
    ui::line("   " + U_DIM + "Final grade" + U_RESET + " " + ui::progress(grade(), 24) + "  " + U_WHITE + U_BOLD + std::to_string(grade()) + "/100" + U_RESET);
    ui::blank();
    ui::line_center(U_DIM + "Keep training, you'll get it next time!" + U_RESET, U_WHITE);
    ui::blank();
    ui::frame_close();
    exit(0);
}

// ==> Creator's message (sponsor command / end of exam)
void exam::sponsor_message(void)
{
    ui::line_center(U_TEAL + U_BOLD + "A word from the creator:" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("  This program has been created entirely " + U_LIME + "for free" + U_RESET + " and " + U_LIME + "open-source" + U_RESET + ".");
    ui::line("  The VIP option exists not to create a business, but simply to help those who enjoy using the program and have a little extra to give.");
    ui::blank();
    ui::line("  If you prefer to contribute without spending money, you can always help out by making a " + U_PINK + U_BOLD + "Pull Request" + U_RESET + ".");
    ui::line("  For those who are just starting out or can't contribute financially, you can also send an email explaining why you'd like VIP status.");
    ui::blank();
    ui::line("  VIP status does not limit the program's core features, it simply offers a few extra options to those who support the project.");
    ui::blank();
    ui::line_center(U_GREEN + U_BOLD + "Thank you for your support, and happy coding! ♥" + U_RESET, U_WHITE);
}

void exam::end_exam()
{
    remove(TOKEN_FILE);
    std::string exam_label = (student ? "Exam Rank 0" : "Exam Week 0") + std::to_string(exam_number);
    std::string exam_id = (student ? "examrank0" : "examweek0") + std::to_string(exam_number);
    ui::frame_open("EXAM COMPLETED", true);
    ui::blank();
    if (using_cheatcode == 0)
    {
        ui::line_center(U_GREEN + U_BOLD + "🥳  CONGRATULATIONS  🥳" + U_RESET, U_WHITE);
        ui::blank();
        ui::line_center("You have finished " + U_LIME + U_BOLD + exam_label + U_RESET + " with " + U_LIME + U_BOLD + "100/100" + U_RESET + " !", U_WHITE);
        send_data("exam_success_end: " + exam_id);
    }
    else
    {
        ui::line_center(U_YELLOW + U_BOLD + "EXAM FINISHED" + U_RESET, U_WHITE);
        ui::blank();
        ui::line_center("You finished " + U_WHITE + U_BOLD + exam_label + U_RESET + " after using " + U_RED + U_BOLD + std::to_string(using_cheatcode) + U_RESET + " cheat command" + (using_cheatcode > 1 ? "s" : "") + "...", U_WHITE);
        send_data("exam_success_cheat" + std::to_string(using_cheatcode) + ": " + exam_id);
    }
    {
        time_t spent = time(0) - start_time;
        if (start_time > 0 && spent > 0)
        {
            std::ostringstream oss;
            oss << spent / 3600 << "h " << std::setw(2) << std::setfill('0') << (spent % 3600) / 60 << "m";
            ui::line_center(U_DIM + "Time spent: " + U_RESET + U_WHITE + oss.str() + U_RESET, U_WHITE);
        }
    }
    ui::blank();
    ui::sep();
    ui::blank();
    sponsor_message();
    ui::blank();
    ui::frame_close();

    std::string c = ui::ask("Open the Github Sponsor page? [y/N]");
    if (c == "y" || c == "Y")
    {
        open_url("https://github.com/sponsors/JCluzet");
        system("cat .system/qrcodesponsor");
    }
    ui::frame_open("THANK YOU", true);
    ui::blank();
    ui::line_center(U_GREEN + U_BOLD + "Thanks for studying with us " + U_WHITE + username + U_GREEN + " ❤" + U_RESET, U_WHITE);
    ui::blank();
    ui::frame_close();
    exit(0);
}

// ==> GradeMe function call by entering `grademe` into prompt
void exam::grademe(void)
{
    if (time(0) >= end_time)
        time_over();
    if (file_exists(".system/grading/beta"))
    {
        ui::frame_open("BETA EXERCISE", false);
        ui::blank();
        ui::line("  " + U_YELLOW + "⚠  Warning: " + U_RESET + "This exercise is a contribution by:");
        std::ifstream file;
        file.open(".system/grading/beta");
        std::string line;
        std::getline(file, line);
        ui::line("  " + U_YELLOW + line + U_RESET);
        ui::line("  It is still in " + U_YELLOW + "beta testing" + U_RESET + ".");
        ui::line("  If you want to add your contribution, visit the Github ReadME 👋");
        ui::line("  If you find any " + U_RED + "bug" + U_RESET + ", please report it on the Github repository.");
        ui::blank();
        ui::frame_close();
        ui::press_enter();
    }

    ui::frame_open("GRADING CONFIRMATION", false);
    ui::blank();
    ui::line("  Before continuing, please make " + U_RED + U_BOLD + "ABSOLUTELY SURE" + U_RESET + " that you are in the right directory, that you didn't forget anything, etc...");
    ui::blank();
    ui::line("  " + U_DIM + "Expected file(s) in" + U_RESET + "  " + U_LIME + ui::truncate(current_path() + "/rendu/" + current_ex->get_name() + "/", ui::text_width() - 24) + U_RESET);
    ui::blank();
    ui::line("  If your assignment is wrong, you will have the same assignment but with " + U_RED + U_BOLD + "less potential points" + U_RESET + " to earn!");
    ui::blank();
    ui::frame_close();
    std::string input = ui::ask(U_RED + "Are you sure? [y/N]" + U_RESET);
    if (input == "y" || input == "Y" || input == "yes")
    {
        if (current_ex->time_bef_grade > time(NULL) && waiting_time)
        {
            long left = (long)(current_ex->time_bef_grade - time(NULL));
            std::string wait = (left >= 60 ? std::to_string(left / 60) + " min " : std::string("")) + std::to_string(left % 60) + " sec";
            ui::frame_open("PATIENCE REQUIRED", false);
            ui::blank();
            ui::line_center(U_YELLOW + U_BOLD + "⏳  " + wait + U_RESET, U_WHITE);
            ui::blank();
            ui::line("  You must wait before your next grading request, so take your time to make more tests and be sure you will succeed next try!");
            ui::blank();
            ui::frame_close();
            ui::press_enter();
            return;
        }
        grade_request(0);
    }
    else
        ui::plain(U_DIM + "Aborted." + U_RESET);
}

// ==> Function that call the bash grade system
void exam::grade_request(bool i)
{
    if (!i)
    {
        ui::frame_open("GRADING IN PROGRESS", false);
        ui::blank();
        ui::line("  We will now wait for the job to complete.");
        ui::line("  Please be " + U_LIME + "patient" + U_RESET + ", this " + U_LIME + "CAN" + U_RESET + " take several minutes... (10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)");
        ui::blank();
        ui::frame_close();
        static std::mt19937 gen(std::random_device{}());
        int waiting_steps = std::uniform_int_distribution<int>(1, 5)(gen);
        for (int i = 0; i < waiting_steps; i++)
        {
            std::cout << "  " << U_DIM << "waiting..." << U_RESET << std::endl;
            usleep(std::uniform_int_distribution<int>(250000, 3000000)(gen));
        }
    }

    if (!file_exists(".system/grading/tester.sh"))
    {
        ui::frame_open("NO GRADER YET", false);
        ui::blank();
        ui::line("  There is no automatic grading script for " + U_WHITE + U_BOLD + current_ex->get_name() + U_RESET + " yet, it's coming soon.");
        ui::line("  Compare your output with the examples in the subject, then use " + U_YELLOW + "force_success" + U_RESET + " (VIP) or " + U_YELLOW + "new_ex" + U_RESET + " (cheat commands) to move on.");
        ui::blank();
        ui::frame_close();
        return;
    }

    remove(".system/grading/passed");
    remove("traceback");
    system("bash .system/grading/tester.sh");

    if (file_exists(".system/grading/passed"))
    {
        remove(".system/grading/passed");
        success_ex(0);
    }
    else
    {
        ui::frame_open("FAILURE", false);
        ui::blank();
        ui::line_center(U_RED + U_BOLD + "✘  FAILURE  ✘" + U_RESET, U_WHITE);
        ui::blank();
        ui::line("  You have failed the assignment.");

        // if there is a traceback file, create a folder traces and copy the file to it with the good name
        if (file_exists("traceback"))
        {
            system("mkdir -p traces");
            std::string trace_name = std::to_string(level) + "-" + std::to_string(current_ex->get_assignement()) + "_" + current_ex->get_name() + ".trace";
            std::string cmd_system_call = "mv traceback traces/" + trace_name;
            system(cmd_system_call.c_str());
            ui::line("  Trace saved to " + U_LIME + ui::truncate(current_path() + "/traces/" + trace_name, ui::text_width() - 17) + U_RESET);
        }
        else
        {
            ui::line("  No traceback found.");
        }
        fail_ex();
        if (waiting_time && current_ex->grade_time() > 0)
            ui::line("  Next grading possible in " + U_YELLOW + U_BOLD + std::to_string((int)(current_ex->grade_time() * 60)) + " sec" + U_RESET + ".");
        ui::blank();
        ui::frame_close();
        ui::press_enter();
        info();
    }
}
