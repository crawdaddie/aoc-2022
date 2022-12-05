#include "./str_utils.h"

void parsef(char *tpl, char *line, ...) {

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

