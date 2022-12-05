#include "./str_utils.h"

void parsef(char *tpl, char *line, ...) {
  /*
   * parsef accepts a newline-terminated template string and input string, and a
   * variable number of int pointers and attempts to extract integers from the
   * input marked by a % in the template and save them to the int pointers
   * for example: parsef("%-%,%-%\n", "8-2,4-5", &arg0, &arg1, &arg2, &arg3);
   * will attempt to find the values 8, 2, 4, 5 in the input string that
   * correspond to the % in the template and save them to each &arg
   */

  va_list argp;
  va_start(argp, line);
  int num = 0;
  int *save_var;
  char stopchar;

  while (*tpl != '\n') {
    if (*tpl == '%') {
      stopchar = *(tpl + 1);
      while(*line != stopchar) {
        num = num * 10 + (*line - '0');
        line++;
      }
      save_var = va_arg(argp, int *);
      *save_var = num;
      num = 0;
      tpl++;
    } else {
      tpl++;
      line++;
    }
  }
  va_end(argp);
}

