#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

char *strduplicate(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = allocate(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

int read_string(char *buf, int buf_siz)
{
    int nr_chars = 0;
    int c;
    do
    {
        c = getchar();
        if (c != '\n' && c != EOF)
        {
            buf[nr_chars] = c;
            ++nr_chars;
        }
        else
        {
            break;
        }
    } while (nr_chars < buf_siz - 1);
    buf[nr_chars] = '\0';
    return nr_chars;
}

bool is_number(char *str)
{
    int length = strlen(str);
    if (length < 1)
    {
        return false;
    }
    else if (length == 1)
    {
        return isdigit(str[0]);
    }
    else
    {
        if (str[0] == '-' || isdigit(str[0]))
        {
            for (int i = 1; i < length; i++)
            {
                if (!isdigit(str[i]))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
    int buf_siz = 255;
    char buf[buf_siz];
    do
    {
        printf("%s\n", question);
        read_string(buf, buf_siz);
    } while (!check(buf));
    return convert(buf);
}

int ask_question_int(char *question)
{
    answer_t answer = ask_question(question, is_number, (convert_func)atoi);
    return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func)strduplicate).string_value;
}

bool is_letter(char *str, char letter)
{
    if (strlen(str) != 1)
    {
        return false;
    }
    else
    {
        return toupper(str[0]) == letter;
    }
}

int string_sum(char *str)
{
    int result = 0;
    do
    {
        result += abs(*str);
    } while (*++str != '\0');
    return result;
}
