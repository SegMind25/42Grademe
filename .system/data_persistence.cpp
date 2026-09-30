#include "exam.hpp"

// ==> Store data of exam in a file
void exam::store_data()
{
    ensure_dir(TOKEN_DIR);
    std::ofstream file(TOKEN_FILE);
    if (!file.is_open())
        return;
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
}

// ==> restore an old version of exam
void exam::restore_data(void)
{
    std::ifstream file(TOKEN_FILE);
    time_t b_start = 0, b_end = 0, b_tbg = 0;
    int b_number = 0, b_level = 0, b_assign = 0, b_level_max = 0;
    int b_per_ex = 0, b_per_ex_save = 0, b_cheat = 0;
    bool b_student = false;
    std::string name;

    bool ok = file.is_open()
        && (file >> b_start >> b_end >> b_number >> b_student >> b_level >> b_assign
                 >> name >> b_level_max >> b_tbg >> b_per_ex >> b_per_ex_save)
        && b_level_max > 0 && b_level >= 0 && b_level < b_level_max && !name.empty();
    if (ok && !(file >> b_cheat))
        b_cheat = 0;
    file.close();

    if (!ok || b_end <= time(0))
    {
        // corrupted or expired backup: start fresh
        remove(TOKEN_FILE);
        ask_param();
        return;
    }

    ui::frame_open("BACKUP FOUND", false);
    ui::blank();
    ui::line_center(U_YELLOW + U_BOLD + "An exam is still in progress" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("   " + U_DIM + "Exam       " + U_RESET + "  " + U_WHITE + U_BOLD + (b_student ? "Exam Rank 0" : "Exam Week 0") + std::to_string(b_number) + U_RESET);
    ui::line("   " + U_DIM + "Exercise   " + U_RESET + "  " + U_LIME + name + U_RESET + U_DIM + "  (level " + std::to_string(b_level) + "/" + std::to_string(b_level_max) + ")" + U_RESET);
    ui::line("   " + U_DIM + "Time left  " + U_RESET + "  " + U_RED + remaining_time(b_end) + U_RESET);
    ui::blank();
    ui::sep();
    ui::card(1, "RESTORE EXAM", "Continue where you left off");
    ui::card(2, "ERASE EXAM", "Delete the backup and start fresh");
    ui::blank();
    ui::frame_close();
    std::string answer = ui::ask("Enter your choice [1-2]");
    while (answer != "1" && answer != "2")
    {
        std::cout << REMOVE_LINE;
        answer = ui::ask("Enter your choice [1-2]");
    }
    if (answer == "1")
    {
        start_time = b_start;
        end_time = b_end;
        exam_number = b_number;
        student = b_student;
        level = b_level;
        level_max = b_level_max;
        level_per_ex = b_per_ex;
        level_per_ex_save = b_per_ex_save;
        using_cheatcode = b_cheat;
        delete current_ex;
        current_ex = new exercise(level, name, b_assign, b_tbg);
        backup = true;
        set_max_time();
        ui::plain(U_LIME + "✔  Exam restored" + U_RESET);
    }
    else
    {
        remove(TOKEN_FILE);
        ask_param();
    }
}

// ==> Load settings file
void exam::load_settings(void)
{
    std::ifstream file(SETTINGS_FILE);
    if (file.is_open())
    {
        bool dse = false, dcc = false, an = false;
        if (file >> dse >> dcc >> an)
        {
            setting_dse = dse;
            setting_dcc = dcc;
            setting_an = an;
        }
    }
}

// ==> Save settings file
void exam::save_settings(void)
{
    ensure_dir(TOKEN_DIR);
    std::ofstream file(SETTINGS_FILE);
    if (file.is_open())
    {
        file << setting_dse << std::endl;
        file << setting_dcc << std::endl;
        file << setting_an << std::endl;
    }
}
