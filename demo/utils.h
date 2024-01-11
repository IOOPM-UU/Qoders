#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

typedef union
{
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool (*check_func)(char *);

typedef answer_t (*convert_func)(char *);

/// @brief reads input from terminal to buffert
/// @param buf where input is to be store
/// @param buf_siz maximum size of string
/// @return size of string
int read_string(char *buf, int buf_siz);

/// @brief check if a given string is a number
/// @param str the string checked
/// @return true if str is a number, false otherwise
bool is_number(char *str);

/// @brief check if a given string is null
/// @param str the string checked
/// @return false if str is null, true otherwise
bool not_empty(char *str);

/// @brief gives a prompt, to be answered with an integer
/// @param question the prompt
/// @return the answer to the prompt in form of an integer
int ask_question_int(char *question);

/// @brief gives a prompt, to be answered with a string
/// @param question the prompt
/// @return the answer to the prompt
char *ask_question_string(char *question);

/// @brief checks if a string is a given letter, uppercase and lowercase both valid
/// @param str the string to check
/// @param letter the given letter to compare the string to
/// @return true if str consists of the uppercase or lowercase version of the given letter
bool is_letter(char *str, char letter);

/// @brief calculates the sum of all letters in a string
/// @param str the given string
/// @return the sum of all the elements in the string
int string_sum(char *str);

char *strduplicate(char *src);

#endif
