#pragma once

#include "ui.hpp"
#include "exercise.hpp"
#include <iostream>
#include <map>

#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sstream>
#include <random>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BOLD std::string("\033[1m")
#define RESET std::string("\033[0m")
#define CYAN std::string("\033[36m")
#define UNDERLINE std::string("\033[4m")
#define WHITE std::string("\033[97m")
#define LIME std::string("\033[92m")
#define RED std::string("\033[91m")
#define MAGENTA std::string("\033[95m")
#define YELLOW std::string("\033[93m")
#define REMOVE_LINE std::string("\033[1A\033[K")

#define TOKEN_DIR ".system/exam_token"
#define TOKEN_FILE ".system/exam_token/current_token.txt"
#define SETTINGS_FILE ".system/exam_token/.settings"

std::string generate_unique_id();
std::string current_path(void);
std::string remaining_time(time_t end_time);
exercise randomize_exercise(std::map<int, exercise> list, bool keep_success);
bool file_exists(std::string path);
void ensure_dir(const std::string &path);
void open_url(const std::string &url);
void send_data(const std::string &event);

void reset_folder(void);
void connexion(void);
void sigc(int sig);
void sigd(void);

class exam
{
public:
    exam(void);
    ~exam(void);
    void info(void);
    void ask_param(void);
    void fail_ex(void);
    void success_ex(bool force);
    void explanation(void);
    int get_exam_number(void);
    int get_lvl(void);
    void store_data();
    void up_lvl(void);
    void exam_help();
    void check_vip(void);
    std::string get_path(void);
    time_t get_end_time(void);
    time_t get_start_time(void);
    int change_ex(void);
    void exam_prompt(void);
    bool prepare_current_ex(void);
    bool clean_all(void);
    void restore_data(void);
    bool start_new_ex(void);
    std::map<int, exercise> list_dir();
    std::map<int, exercise> list_ex_lvl;
    std::map<int, exercise> lvl_ex;
    exercise *current_ex;
    bool student;
    bool waiting_time;
    int level_max;
    bool changex;

private:
    exam(exam const &src);            // not copyable (owns current_ex)
    exam &operator=(exam const &src);

    void set_max_time(void);
    void grademe(void);
    void settings_menu(void);
    void grade_request(bool i);
    void exam_random_show(void);
    void end_exam(void);
    void time_over(void);
    void sponsor_message(void);
    void set_max_lvl(void);
    int grade(void);
    int stud_menu(void);
    void load_settings(void);
    void save_settings(void);
    int piscine_menu(void);
    int stud_or_swim(void);
    void backtracking_menu(void);

    bool setting_dse;
    bool setting_dcc;
    bool setting_an;
    std::string username;

    time_t start_time;
    time_t end_time;

    bool reelmode;
    int level_per_ex_save;
    int time_max;
    int exam_number;
    int using_cheatcode;
    bool vip;
    int level_per_ex;
    int level;
    bool backup;
};
