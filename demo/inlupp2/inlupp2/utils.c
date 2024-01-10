#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
extern char *strdup(const char *);
#include "utils.h"



bool is_number(char *str)
{
  int length = strlen(str);
 
  for (int i = 0; i < length; i++) {

    int check_char = str[i];

    if(check_char == 45 && i == 0 && length >= 2) {
      continue;
    }
    
    if(check_char < 48 || 57 < check_char) {
        return false;
    } 
  }
   return true;
}


int read_string(char *buf, int buf_size) {
  char c = getchar();
  int count = 0;
    while (c != '\n' && count < buf_size) {
      buf[count] = c;
      count++;
      c = getchar();
    }
    buf[count] = '\0';
    return count;
}

bool not_empty(char *str)
{
  int length = strlen(str);
  if (length > 0)
  {
    for (int i = 0; i < length; i++)
    {
      int check_char = str[i];
      if (check_char < 48 && check_char > 57)
      {
        printf("Insert a string.\n");
        return false;
      }
    }
  }
  return true;
}

bool is_correct_format(char *str)
{
  // int new_adress =  str + sizeof(char *);
  if(strlen(str) > 3)
  {
    printf("Invalid format, please enter a character and two following numbers.\n");
    return false;
  }
  char first_char = str[0]; 
                                             
  if( (first_char > 64 && first_char < 91) && is_number(++str)) {
      return true;
  }
   return false;
}
//DU ANVÄNDE INTE DET NEDANSTÅENDE 
//  Som konverteringsfunktion fungerar strdup() eftersom representationen för lagerhyllan är en sträng.

answer_t ask_question(char *question, check_func check, convert_func convert) {

    char buffer[100] = {0};
    answer_t result; 

    do 
    {
        printf("%s ", question);
        read_string(buffer, sizeof(buffer)/sizeof(buffer[0]));
    }
    while(!(check(buffer)));
    
    result = convert(buffer);
    return result;
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
  answer_t answer = ask_question(question, not_empty, (convert_func) strdup);
  return answer.string_value;

}

char *ask_question_shelf(char *question) {
  
  answer_t answer = ask_question(question, is_correct_format, (convert_func) strdup);
  return answer.string_value;

}
