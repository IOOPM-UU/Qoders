#ifndef __UTILS_H__
#define __UTILS_H__
extern char *strdup(const char *);
#include <stdbool.h>

//Union som representerar olika datatyper
typedef union
{
    int   int_value;
    float float_value;
    char *string_value;
} answer_t;

//Typen på kontrollfunktionen
typedef bool(*check_func )(char *);

//Typen på konverteringsfunktionen
typedef answer_t(*convert_func)(char *);

/*//////////////FUNCTIONS//////////////////*/


int ask_question_int(char *question);
char *ask_question_string(char *question);
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
char *ask_question_shelf(char *question);


#endif



// char *ask_question_string(char *question, char *buf, int buf_siz);
// bool is_float(char *str);
// answer_t make_float(char *str);
// bool not_empty(char *str);
// double ask_question_float(char *question);


// void println(char *word);
// void print(char *word);