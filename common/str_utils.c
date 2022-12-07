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
      while (*line != stopchar) {
        num = num * 10 + (*line - '0'); // collect digits from the input string
                                        // until you reach the stopchar
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

void parse_int(va_list *argp, char **line, char stopchar) {
  int num = 0;
  while (**line != stopchar) {
    num = num * 10 + (**line - '0'); // collect digits from the input string
                                     // until you reach the stopchar
    (*line)++;
  }
  int *save_var = va_arg(*argp, int *);
  *save_var = num;
}

void parse_str(va_list *argp, char **line, char stopchar) {
  int len = 0;
  while (**line != stopchar) {
    len++; // until you reach the stopchar
    (*line)++;
  }

  char *cp = malloc(sizeof(char) * len);
  char *save_var = va_arg(*argp, char *);
  /* strcpy(cp, *line - len); */
  printf("string to get %s\n", (*line - len));
  save_var = (*line - len);
}

void parsef_dyn(char *tpl, char *line, ...) {
  va_list argp;
  va_start(argp, line);
  int num = 0;
  int *save_var;
  char stopchar;
  char parsef_type;

  while (*tpl != '\n') {
    if (*tpl == '%') {
      parsef_type = *(tpl + 1);
      tpl++;

      stopchar = *(tpl + 1);
      printf("type: %c stop '%c'\n", parsef_type, stopchar);
      switch (parsef_type) {
      case 'd':
        parse_int(&argp, &line, stopchar);
        break;

      case 's':
        parse_str(&argp, &line, stopchar);
        break;
      default:
        while (*line != stopchar) {
          line++;
        }
      }

      tpl++;
    } else {
      tpl++;
      line++;
    }
  }
  va_end(argp);
}
