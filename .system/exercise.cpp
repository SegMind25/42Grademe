#include "exam.hpp"

exercise::exercise(void) {
    this->name = "UNKNOWN";
    assignement = 0;
    level_ex = 0;
    time_bef_grade = time(NULL);
}

// ==> Function to change exercise
int exam::change_ex(void)
{
    // after restoring a backup the level list isn't loaded yet
    if (list_ex_lvl.empty())
        list_ex_lvl = list_dir();
    // if there is only 1 exercise, we can't change it
    if (list_ex_lvl.size() <= 1)
    {
        ui::plain(U_YELLOW + "⚠  You can't change exercise, there is only one exercise in this level" + U_RESET);
        return (0);
    }
    backup = false;
    changex = 1;
    clean_all();
    start_new_ex();
    ui::plain(U_LIME + "✔  You have generated a new exercise" + U_RESET);
    return (0);
}

// ==> Set good folder and copy subjects, etc...
bool exam::prepare_current_ex(void)
{
    if (level >= level_max)
        return (false);
    if (!file_exists(get_path()))
    {
        ui::plain(U_RED + "✘  Error: Cannot load exercise, unable to find valid path" + U_RESET);
        return (false);
    }

    // clean all old files
    clean_all();

    // create directory for the current exercise
    ensure_dir("rendu");
    ensure_dir("subjects");
    ensure_dir(".system/grading");

    // subject (attachment/*) goes to subjects/, grading files to .system/grading/
    std::string cmd_system_call = "cp -r " + get_path() + "attachment/* subjects/ 2>/dev/null";
    system(cmd_system_call.c_str());
    cmd_system_call = "cp " + get_path() + "* .system/grading/ >/dev/null 2>&1";
    system(cmd_system_call.c_str());
    return (true);
}

// ==> Randomize exercise (give 1 into list)
// keep_success == false removes exercises listed in success/success_ex
exercise randomize_exercise(std::map<int, exercise> list, bool keep_success)
{
    if (!keep_success)
    {
        std::ifstream success_ex("success/success_ex");
        std::string line;
        while (std::getline(success_ex, line))
        {
            std::istringstream iss(line);
            std::string name;
            iss >> name;
            for (std::map<int, exercise>::iterator it = list.begin(); it != list.end(); it++)
            {
                if (it->second.get_name() == name)
                {
                    list.erase(it);
                    break;
                }
            }
        }
    }

    if (list.empty())
    {
        ui::frame_open("NO EXERCISES LEFT", false);
        ui::blank();
        ui::line(U_RED + "  You already passed every exercise of this level." + U_RESET);
        ui::blank();
        ui::line("  Turn " + U_GREEN + U_BOLD + "ON" + U_RESET + " option 1 (" + U_WHITE + "Enable exercises you already passed" + U_RESET + ") in settings,");
        ui::line("  or edit/delete the file " + U_LIME + "success/success_ex" + U_RESET + ".");
        ui::line("  Then relaunch 42_EXAM to recover your exam.");
        ui::blank();
        ui::frame_close();
        exit(0);
    }

    static std::mt19937 gen(std::random_device{}() ^ (unsigned int)time(NULL));
    std::uniform_int_distribution<size_t> distr(0, list.size() - 1);
    std::map<int, exercise>::iterator it = list.begin();
    std::advance(it, distr(gen));
    return (it->second);
}

exercise::exercise(int level, std::string ex_name) {
    this->name = ex_name;
    level_ex = level;
    assignement = 0;
    time_bef_grade = time(NULL);
}

exercise::exercise(int level, std::string ex_name, int assign, time_t tbg) {
    this->name = ex_name;
    level_ex = level;
    assignement = assign;
    time_bef_grade = tbg;
}

exercise::exercise(exercise const & src) {
    this->name = src.name;
    level_ex = src.level_ex;
    assignement = src.assignement;
    time_bef_grade = src.time_bef_grade;
}

exercise::~exercise(void) {
}

exercise&  exercise::operator=(exercise const & src) {
    this->name = src.name;
    level_ex = src.level_ex;
    assignement = src.assignement;
    time_bef_grade = src.time_bef_grade;
    return (*this);
}


// ==> GETTER/SETTER
void exercise::set_time_bef_grade(time_t time)
{
    time_bef_grade = time;
}

std::string exercise::get_name(void) {
    return (this->name);
}

void exercise::reset_assignement(void)
{
    assignement = 0;
}

void exercise::up_assignement(void) {
    this->assignement++;
}

int exercise::get_lvl(void) {
    return (this->level_ex);
}

void exercise::up_lvl(void) {
    level_ex++;
}

int exercise::get_assignement(void) {
    return (this->assignement);
}

void exercise::set_assignement(int assignement) {
    this->assignement = assignement;
}