#include "exam.hpp"

// ==> Store data of exam in a file
void exam::store_data()
{
    std::ofstream file;

    file.open(".system/exam_token/current_token.txt");
    file << get_start_time() << std::endl;
    file << get_end_time() << std::endl;
    file << get_exam_number() << std::endl;
    file << student << std::endl;
    file << get_lvl() << std::endl;
    file << current_ex->get_assignement() << std::endl;
    file << current_ex->get_name() << std::endl;
    file << level_max << std::endl;
    file << current_ex->time_bef_grade << std::endl;
    file << level_per_ex << std::endl;
    file << level_per_ex_save << std::endl;
    file << using_cheatcode << std::endl;

    file.close();
}

// ==> restore an old version of exam
void exam::restore_data(void)
{
    std::ifstream file;
    exam backup;
    std::string name;
    std::string assign;
    std::string time_bef_grade;
    time_t t;
    file.open(".system/exam_token/current_token.txt", std::ios::in);
    if (file.is_open())
    {
        file >> backup.start_time;
        file >> backup.end_time;
        file >> backup.exam_number;
        file >> backup.student;
        file >> backup.level;
        file >> assign;
        file >> name;
        file >> backup.level_max;
        file >> time_bef_grade;
        file >> backup.level_per_ex;
        file >> backup.level_per_ex_save;
        file >> backup.using_cheatcode;

        backup.current_ex = new exercise(backup.get_lvl(), name, std::stoi(assign), std::stoi(time_bef_grade));
        backup.backup = 1;
        file.close();
    }
    else
    {
        std::cout << "Error: can't open backup" << std::endl;
    }

    file.close();

    if (backup.end_time > time(0))
    {
        ui::frame_open("BACKUP FOUND", false);
        ui::blank();
        ui::line_center(U_RED + U_BOLD + "!!  BACKUP  !!" + U_RESET, U_WHITE);
        ui::blank();
        if (backup.student)
            ui::line_center(U_WHITE + "EXAMRANK " + U_LIME + "0" + std::to_string(backup.exam_number) + U_RESET, U_WHITE);
        else
            ui::line_center(U_WHITE + "EXAMWEEK " + U_LIME + "0" + std::to_string(backup.exam_number) + U_RESET, U_WHITE);
        ui::line("  " + U_DIM + "Current ex" + U_RESET + "   " + U_LIME + backup.current_ex->get_name() + U_RESET);
        ui::line("  " + U_DIM + "Time left" + U_RESET + "   " + U_RED + remaining_time(backup.end_time) + U_RESET);
        ui::blank();
        ui::sep();
        ui::blank();
        ui::card(1, "RESTORE EXAM", "Continue where you left off");
        ui::blank();
        ui::card(2, "ERASE EXAM", "Delete the backup and start fresh");
        ui::blank();
        ui::frame_close();
        ui::prompt("Enter your choice [1-2]");
        std::string answer;
        std::getline(std::cin, answer);
        while (answer != "1" && answer != "2")
        {
            std::cout << REMOVE_LINE;
            ui::prompt("Enter your choice [1-2]");
            std::getline(std::cin, answer);
        }
        if (answer == "1")
        {
            std::cout << std::endl
                      << U_LIME << "   ✔  Restoring exam token..." << U_RESET << std::endl
                      << std::endl;
            this->start_time = backup.get_start_time();
            this->end_time = backup.get_end_time();
            this->exam_number = backup.get_exam_number();
            this->student = backup.student;
            this->level = backup.get_lvl();
            this->current_ex = backup.current_ex;
            this->backup = backup.backup;
            this->level_max = backup.level_max;
            this->level_per_ex = backup.level_per_ex;
            this->level_per_ex_save = backup.level_per_ex_save;
            this->using_cheatcode = backup.using_cheatcode;
        }
        else
        {
            std::cout << "   Exam token deleted" << std::endl;
            // delete file and return to menu
            system("rm .system/exam_token/current_token.txt");
            ui::clear();
            ask_param();
        }
    }
    else
        ask_param();
}

// ==> Load .settings file into setting_dse bool
void exam::load_settings(void)
{
    std::ifstream file(".system/exam_token/.settings");
    std::string line;
    if (file.is_open())
    {
        file >> setting_dse;
        file >> setting_dcc;
        file >> setting_an;
        file.close();
    }
}

// ==> Save setting_dse bool into .settings file
void exam::save_settings(void)
{
    std::ofstream file(".system/exam_token/.settings");
    if (file.is_open())
    {
        file << setting_dse << std::endl;
        file << setting_dcc << std::endl;
        file << setting_an << std::endl;
        file.close();
    }
}
