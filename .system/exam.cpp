#include "exam.hpp"

// ==> Store all possible exercises in a map
std::map<int, exercise> exam::list_dir(void)
{
    struct dirent *entry;
    int i = 0;
    std::map<int, exercise> list;
    std::string path;
    if (student)
        path = ".subjects/STUD_PART/exam_0" + std::to_string(exam_number) + "/" + std::to_string(level) + "/";
    else
        path = ".subjects/PISCINE_PART/exam_0" + std::to_string(exam_number) + "/" + std::to_string(level) + "/";

    DIR *dir = opendir(path.c_str());
    std::string folder;
    if (dir == NULL)
    {
        ui::frame_open("ERROR", false);
        ui::blank();
        ui::line(U_RED + "  Can't open the exercise directory:" + U_RESET);
        ui::line("  " + U_WHITE + path + U_RESET);
        ui::blank();
        ui::line("  Your copy of 42_EXAM may be incomplete, try " + U_LIME + "git pull" + U_RESET + ".");
        ui::blank();
        ui::frame_close();
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL)
    {
        folder = entry->d_name;
        if (folder.empty() || folder[0] == '.')
            continue;
        if (!file_exists(path + folder + "/tester.sh") && !file_exists(path + folder + "/attachment"))
            continue;
        list.insert(std::pair<int, exercise>(i, exercise(get_lvl(), folder)));
        i++;
    }
    closedir(dir);
    return (list);
}

// ==> Get path of actual exercise
std::string exam::get_path(void)
{
    std::string path_exam;

    if (student)
        path_exam = ".subjects/STUD_PART/exam_0" + std::to_string(exam_number) + "/" + std::to_string(level) + "/" + current_ex->get_name() + "/";
    else
        path_exam = ".subjects/PISCINE_PART/exam_0" + std::to_string(exam_number) + "/" + std::to_string(level) + "/" + current_ex->get_name() + "/";
    return (path_exam);
}

// ==> Set max level for an exam
void exam::set_max_lvl(void)
{
    if (student)
    {
        if (exam_number == 2)
            level_max = 4;
        else if (exam_number == 3)
            level_max = 1;
        else if (exam_number == 4)
            level_max = 1;
        else if (exam_number == 5)
            level_max = 3;
        else if (exam_number == 6)
            level_max = 1;
    }
    else
    {
        if (exam_number == 1 || exam_number == 2)
            level_max = 8;
        else
            level_max = 4;
    }
}

// ==> Set max hrs for exam (3 or 4)
void exam::set_max_time(void)
{
    if (student)
        time_max = 180;
    else
    {
        if (exam_number == 4)
            time_max = 480;
        else
            time_max = 240;
    }
}

void exam::explanation(void)
{
    ui::frame_open("HOW THE EXAM WORKS", false);
    ui::blank();
    ui::line("  " + U_YELLOW + "⚠" + U_RESET + "  You have to work from a new window to keep this one " + U_LIME + "available" + U_RESET);
    ui::blank();
    ui::line("  " + U_YELLOW + "📝" + U_RESET + "  A random subject named " + U_LIME + "subject.en.txt" + U_RESET + " will be generated.");
    ui::line("        > You must write your file (example.c) in the assign folder (see subject),");
    ui::line("          this folder must be inside the folder: " + U_LIME + "rendu" + U_RESET);
    ui::blank();
    ui::line("  " + U_YELLOW + "🎓" + U_RESET + "  Once completed, you can push/correct your project with: " + U_LIME + "grademe" + U_RESET);
    ui::line("        > If your level is validated, you move on to the next level 🎉");
    ui::line("        > If not, you have to start again ❌");
    ui::blank();
    ui::line("  " + U_YELLOW + "⌛" + U_RESET + "  Warning: the more you try to get the same project corrected,");
    ui::line("          the longer you will have to wait to get it " + U_LIME + "corrected" + U_RESET + ".");
    ui::blank();
    ui::line("  " + U_YELLOW + "📌" + U_RESET + "  Nice reminder: here you don't need to use GIT.");
    ui::line("          Remember that during the exam you will have to use it to push your project!");
    ui::blank();
    ui::sep();
    ui::line(U_MAGENTA + U_BOLD + "  RGPD INFORMATION:" + U_RESET);
    ui::line("     The data that can be collected are:");
    ui::line("       - The host name of your machine. (can be set to anonyme in menu)");
    ui::line("       - The exam number you choose.");
    ui::line("       - Name of exercise, fail or success, current assignement and level.");
    ui::blank();
    ui::sep();
    ui::line(U_MAGENTA + U_BOLD + "  🚀 GRADEME VIP (0€ - 3€):" + U_RESET);
    ui::line("     You can become VIP by contributing to the repo, making a " + U_PINK + "Pull Request" + U_RESET);
    ui::line("     OR " + U_LIME + "Sponsor Github Page" + U_RESET + " (use " + U_PINK + "sponsor" + U_RESET + " for more info):");
    ui::line("       - Instant correction with new " + U_PINK + "gradenow" + U_RESET + " command");
    ui::line("       - Force an exercise to succeed with " + U_PINK + "force_success" + U_RESET + " command");
    ui::line("       - Having the " + U_PINK + "SAME display condition" + U_RESET + " as 42 school");
    ui::line("       - More coming...");
    ui::blank();
    ui::sep();
    ui::line("  " + U_RED + U_BOLD + "‼  DISCLAIMER:" + U_RESET);
    ui::line("      This program is " + U_RED + "not" + U_RESET + " the real 42 exam and is " + U_RED + "not" + U_RESET + " made by 42.");
    ui::line("      It is created by a student, free and open-source.");
    ui::blank();
    ui::frame_close();
    ui::press_enter();
}


// ==> First menu asking examrank number
void exam::ask_param(void)
{
    int select = 0;
    reset_folder();
    while (1)
    {
        exam_number = 0;
        while (exam_number == 0)
        {
            if (exam_number == 0)
                select = stud_or_swim();
            if (select == 1)
            {
                student = false;
                exam_number = piscine_menu();
            }
            else if (select == 2)
            {
                student = true;
                exam_number = stud_menu();
            }
        }
        set_max_lvl();
        set_max_time();
        ui::frame_open("REGISTRATION", false);
        ui::blank();
        ui::line_center((student ? "EXAM RANK 0" : "EXAM WEEK 0") + std::to_string(exam_number), std::string(U_BOLD) + U_LIME);
        ui::blank();
        ui::line("   " + U_DIM + "Levels   " + U_RESET + "  " + U_WHITE + U_BOLD + std::to_string(level_max) + U_RESET);
        ui::line("   " + U_DIM + "Duration " + U_RESET + "  " + U_WHITE + U_BOLD + std::to_string(time_max / 60) + "h" + U_RESET);
        ui::blank();
        ui::frame_close();
        std::string confirm = ui::ask("Confirm registration? [" + U_LIME + "y" + U_RESET + U_BOLD + "/n]");
        if (confirm == "y" || confirm == "Y" || confirm == "yes")
            break;
    }

    level_per_ex = 100 / level_max;
    level_per_ex_save = level_per_ex;

    // SEND DATA ABOUT CHOOSEN EXAM
    send_data((student ? "choose_examrank0" : "choose_examweek0") + std::to_string(exam_number));
    explanation();
    // =============================

    // CONNEXION ANIMATION
    connexion();
    ui::frame_open("EXAM READY", false);
    ui::blank();
    ui::line_center(U_LIME + U_BOLD + "✔  You're connected, " + U_WHITE + username + U_LIME + "!" + U_RESET, U_WHITE);
    ui::blank();
    ui::line("  You can log out at any time. If this program tells you you earned points,");
    ui::line("  then they will be counted whatever happens.");
    ui::blank();
    ui::sep();
    ui::blank();
    ui::line("  " + U_DIM + "Project" + U_RESET + "   " + U_WHITE + U_BOLD
             + (student ? "ExamRank0" + std::to_string(exam_number) : "ExamWeek0" + std::to_string(exam_number))
             + U_RESET + "  in " + U_MAGENTA + U_BOLD + "REAL" + U_RESET + " mode");
    ui::line("  " + U_DIM + "Start lvl" + U_RESET + " " + U_YELLOW + U_BOLD + std::to_string(level) + U_RESET);
    ui::line("  " + U_DIM + "Duration" + U_RESET + "   " + U_LIME + U_BOLD + std::to_string(time_max / 60) + "h" + U_RESET);
    ui::blank();
    ui::frame_close();
    ui::press_enter("Press a key to start exam 🏁");
    // ====================

    // TIME SETUP
    start_time = time(0);
    end_time = start_time + (60 * time_max);

}

std::string generate_unique_id()
{
    std::ifstream infile(".system/unique_id.txt");
    if (infile.good())
    {
        std::string id;
        std::getline(infile, id);
        infile.close();
        return id;
    }
    else
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1000000, 9999999);

        std::string id = std::to_string(distr(gen));

        std::ofstream outfile(".system/unique_id.txt");
        outfile << id;
        outfile.close();

        return id;
    }
}

// CONSTRUCTOR/OPERATOR/GETTER/SETTER
exam::exam(void)
    : current_ex(NULL), student(false), waiting_time(true), level_max(1), changex(false),
      setting_dse(false), setting_dcc(false), setting_an(false),
      start_time(0), end_time(0), reelmode(true), level_per_ex_save(0), time_max(0),
      exam_number(0), using_cheatcode(0), vip(false), level_per_ex(0), level(0), backup(false)
{
    username = getenv("USER") ? getenv("USER") : "unknown";
    load_settings();
    if (setting_an)
        setenv("LOGNAMELOG42EXAM", generate_unique_id().c_str(), 1);
}

exam::~exam(void)
{
    delete current_ex;
}

// ==> Check (once, with a short timeout) whether the user is a VIP
void exam::check_vip(void)
{
    vip = false;
    std::string cmd = "curl -s -f --max-time 3 https://user.grademe.fr/vip_list > .system/vip_list 2>/dev/null";
    if (system(cmd.c_str()) == 0)
    {
        std::ifstream vip_list(".system/vip_list");
        std::string line;
        while (std::getline(vip_list, line))
        {
            if (!line.empty() && line[line.size() - 1] == '\r')
                line.erase(line.size() - 1);
            if (line == username)
            {
                vip = true;
                break;
            }
        }
    }
    remove(".system/vip_list");
}

void exam::up_lvl(void)
{
    level++;
}

time_t exam::get_end_time(void)
{
    return (end_time);
}

time_t exam::get_start_time(void)
{
    return (start_time);
}

int exam::get_lvl(void)
{
    return (level);
}

int exam::get_exam_number()
{
    return (exam_number);
}