#include "./str_utils.h"

void parsef(char *tpl, char *line, ...) {
  printf("%s : %s\n", tpl, line);

  va_list argp;
  va_start(argp, line);
  int num = 0;
  int *save_var;

  while (*line != '\n' || *line != '\0') {

    if (*line == '-' || *line == ',') {
      save_var = va_arg(argp, int *);
      *save_var = num;
      num = 0;
    } else {
      num = num * 10 + (*line - '0');
    }
    line++;
  }

  save_var = va_arg(argp, int *);
  *save_var = num;

  va_end(argp);
}
