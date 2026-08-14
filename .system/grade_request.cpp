#include "exam.hpp"

void exam::fail_ex()
{
    std::string tmp = "bash .system/data_sender.sh \"fail_ex:" + current_ex->get_name() + " level:" + std::to_string(level) + " assignement:" + std::to_string(current_ex->get_assignement()) + "\"";
    system(tmp.c_str());
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
        std::ofstream file;
        file.open("success/success_ex", std::ios::app);
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
    ui::blank();
    ui::frame_close();
    std::string tmp;
    if (force)
        tmp = "bash .system/data_sender.sh \"cheat_success_ex: " + current_ex->get_name() + " level:" + std::to_string(level) + " assignment:" + std::to_string(current_ex->get_assignement()) + "\"";
    else
        tmp = "bash .system/data_sender.sh \"success_ex: " + current_ex->get_name() + " level:" + std::to_string(level) + " assignment:" + std::to_string(current_ex->get_assignement()) + "\"";
    system(tmp.c_str());
    up_lvl();
    ui::press_enter("Moving to the next exercise...");
    level_per_ex += level_per_ex_save;
    changex = 0;
    backup = 0;
    if (!force)
    {
        if (file_exists("rendu/"))
        {
            if (!file_exists("success"))
                system("mkdir success");
            system("cp -r rendu/* success/ 2> /dev/null");
        }
    }
    if (level_per_ex > 100)
        end_exam();
    start_new_ex();
}

void exam::end_exam()
{
    std::string tmp;
    remove(".system/exam_token/current_token.txt");
    ui::frame_open("EXAM COMPLETED", true);
    ui::blank();
    if (using_cheatcode == 0)
    {
        ui::line_center(U_GREEN + U_BOLD + "🥳  CONGRATULATIONS  🥳" + U_RESET, U_WHITE);
        ui::blank();
        if (student)
            ui::line_center("You have finished " + U_LIME + U_BOLD + "Exam Rank 0" + std::to_string(exam_number) + U_RESET + " !", U_WHITE);
        else
            ui::line_center("You have finished " + U_LIME + U_BOLD + "Exam Week 0" + std::to_string(exam_number) + U_RESET + " !", U_WHITE);
        if (student)
            tmp = "bash .system/data_sender.sh \"exam_success_end: examrank0" + std::to_string(exam_number) + "\"";
        else
            tmp = "bash .system/data_sender.sh \"exam_success_end: examweek0" + std::to_string(exam_number) + "\"";
        system(tmp.c_str());
    }
    else
    {
        ui::line_center(U_RED + U_BOLD + "EXAM FINISHED" + U_RESET, U_WHITE);
        ui::blank();
        if (student)
            ui::line_center("You finished " + U_WHITE + U_BOLD + "Exam Rank 0" + std::to_string(exam_number) + U_RESET + " after using " + U_RED + U_BOLD + std::to_string(using_cheatcode) + U_RESET + " cheat command...", U_WHITE);
        else
            ui::line_center("You finished " + U_WHITE + U_BOLD + "Exam Week 0" + std::to_string(exam_number) + U_RESET + " after using " + U_RED + U_BOLD + std::to_string(using_cheatcode) + U_RESET + " cheat command...", U_WHITE);
        if (student)
            tmp = "bash .system/data_sender.sh \"exam_success_cheat" + std::to_string(using_cheatcode) + ": examrank0" + std::to_string(exam_number) + "\"";
        else
            tmp = "bash .system/data_sender.sh \"exam_success_cheat" + std::to_string(using_cheatcode) + ": examweek0" + std::to_string(exam_number) + "\"";
        system(tmp.c_str());
    }
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line_center(U_TEAL + U_BOLD + "A word from the creator:" + U_RESET, U_WHITE);
    ui::blank();
    ui::line(U_WHITE + "  This program has been created entirely " + U_LIME + "for free" + U_RESET + U_WHITE + " and " + U_LIME + "open-source" + U_RESET + U_WHITE + "." + U_RESET);
    ui::line(U_WHITE + "  The VIP option exists not to create a business, but simply to help" + U_RESET);
    ui::line(U_WHITE + "  those who enjoy using the program and have a little extra to give." + U_RESET);
    ui::line(U_WHITE + "  If you're a student who loves this tool and wants to support my journey," + U_RESET);
    ui::line(U_WHITE + "  consider becoming a VIP by making a small donation." + U_RESET);
    ui::line(U_WHITE + "  However, if you prefer to contribute without spending money, you can" + U_RESET);
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

    std::cout << U_WHITE << U_BOLD << "  Open the Github Sponsor Page? (y/n) " << U_RESET;
    char c;
    std::cin >> c;
    if (c == 'y' || c == 'Y')
    {
        int is_linux = 0;
#ifdef __linux__
        is_linux = 1;
#endif
        if (is_linux)
            system("xdg-open https://github.com/sponsors/JCluzet");
        else
            system("open https://github.com/sponsors/JCluzet");
        system("cat .system/qrcodesponsor");
    }
    ui::clear();
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
    if (file_exists(".system/grading/beta"))
    {
        ui::clear();
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
    }

    ui::clear();
    ui::frame_open("GRADING CONFIRMATION", false);
    ui::blank();
    ui::line("  Before continuing, please make " + U_RED + U_BOLD + "ABSOLUTELY SURE" + U_RESET + " that you are in the right directory,");
    ui::line("  that you didn't forget anything, etc...");
    ui::line("  If your assignment is wrong, you will have the same assignment");
    ui::line("  but with " + U_RED + U_BOLD + "less potential points" + U_RESET + " to earn !");
    ui::blank();
    ui::frame_close();
    ui::prompt(U_RED + "Are you sure? [y/N]" + U_RESET);
    std::string input;
    if (!std::getline(std::cin, input))
        sigd();
    if (input == "y" || input == "Y")
    {
        if (current_ex->time_bef_grade > time(NULL) && waiting_time)
        {
            ui::clear();
            ui::frame_open("PATIENCE REQUIRED", false);
            ui::blank();
            ui::line("  " + U_RED + "ERROR: " + U_RESET + "You must wait at least " + U_YELLOW + U_BOLD);
            if ((((current_ex->time_bef_grade - time(NULL))) / 60) >= 1)
                ui::line("  " + std::to_string((current_ex->time_bef_grade - time(NULL)) / 60) + " minutes and " + std::to_string((current_ex->time_bef_grade - time(NULL)) % 60) + " seconds");
            else
                ui::line("  " + std::to_string(current_ex->time_bef_grade - time(NULL)) + " seconds");
            ui::line("  until next grading request, so take your time to make more tests");
            ui::line("  and be sure you will succeed next try!");
            ui::blank();
            ui::frame_close();
            ui::press_enter();
            return;
        }
        ui::clear();
        ui::frame_open("GRADING", false);
        ui::blank();
        ui::line_center(U_YELLOW + "⏳  Sending grading request to the server..." + U_RESET, U_WHITE);
        ui::blank();
        ui::frame_close();
        grade_request(0);
    }
    else
    {
        std::cout << "  Abort" << std::endl;
    }
}

// ==> Function that call the bash grade system
void exam::grade_request(bool i)
{
    if (!i)
    {
        ui::clear();
        ui::frame_open("GRADING IN PROGRESS", false);
        ui::blank();
        ui::line("  We will now wait for the job to complete.");
        ui::line("  Please be " + U_LIME + "patient" + U_RESET + ", this " + U_LIME + "CAN" + U_RESET + " take several minutes...");
        ui::line("  (10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)");
        ui::blank();
        ui::frame_close();
        srand(time(NULL));
        int waiting_seconds = rand() % 5 + 1;
        for (int i = 0; i < waiting_seconds; i++)
        {
            srand(time(NULL));
            double random = rand() % 6500000 + 250000;
            std::cout << "  waiting..." << std::endl;
            usleep(random);
        }
    }

    if (!file_exists(".system/grading/tester.sh"))
    {
        ui::clear();
        ui::frame_open("ERROR", false);
        ui::blank();
        ui::line("  Unable to find grading script for this exercise, it's coming soon.");
        ui::line("  You can use " + U_YELLOW + "\"force_success\"" + U_RESET + " to pass this ex.");
        ui::blank();
        ui::frame_close();
        return;
    }

    system("bash .system/grading/tester.sh");

    if (file_exists(".system/grading/passed"))
    {
        success_ex(0);
    }
    else
    {
        ui::clear();
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
            ui::line("  Trace saved to " + U_LIME + current_path() + "/traces/" + trace_name + U_RESET);
        }
        else
        {
            ui::line("  No traceback found.");
        }
        ui::blank();
        ui::frame_close();
        sleep(1);
        fail_ex();
        ui::press_enter();
        if (vip)
            infovip();
        else
            info();
    }
}
