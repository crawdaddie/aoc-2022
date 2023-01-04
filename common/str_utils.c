#include "./str_utils.h"

void parsef_int(char *tpl, char *line, ...) {
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

int parse_int(char **line, char stopchar) {
  int num = 0;
  int neg = 1;
  if (**line == '-') {
    neg = -1;
    (*line)++;
  } else {
    neg = 1;
  };
  while (**line != stopchar) {
    num = num * 10 + (**line - '0'); // collect digits from the input string
    (*line)++;
  }
  return num * neg;
}

int is_stopchar(char **line, char *stopchar, int num_stopchars) {
  for (int i = 0; i < num_stopchars; i++) {
    if (**line == stopchar[i]) {
      return 1;
    }
  }
  return 0;
}

void parse_int_n(char **line, char *stopchars, int num_stopchars, int *val) {
  int num = 0;
  int neg = 1;
  int pos = 0;
  if (**line == '-') {
    neg = -1;
    (*line)++;
    pos++;
  } else {
    neg = 1;
  };

  while (!is_stopchar(line, stopchars, num_stopchars)) {
    num = num * 10 + (**line - '0'); // collect digits from the input string
    (*line)++;
    pos++;
  }

  *val = num * neg;
}

char *parse_str(char **line, char stopchar) {
  int len = 0;
  while (**line != stopchar) {
    len++; // until you reach the stopchar
    (*line)++;
  }
  char *cp = malloc(sizeof(char) * len);
  /* strcpy(cp, *line - len); */
  /* printf("copy %s\n", cp); */
  /* return cp; */
  return (*line - len);
}

int find_char_idx(char *line, char stopchar) {
  int idx;
  while (line[idx] != '\0') {
    if (line[idx] == stopchar) {
      return idx;
    }
    idx++;
  }
  return -1;
};

void parsef(char *tpl, char *line, ...) {
  va_list argp;
  va_start(argp, line);

  char stopchar;
  char parsef_type;

  while (*tpl != '\0') {
    if (*tpl == '%') {
      parsef_type = *(tpl + 1);
      tpl++;

      stopchar = *(tpl + 1);
      switch (parsef_type) {
      case 'd': {
        int *save_var = va_arg(argp, int *);
        *save_var = parse_int(&line, stopchar);
      } break;

      case 's': {
        char **save_var = (char **)va_arg(argp, char **);
        *save_var = strsep(&line, &stopchar);
      } break;

      case 'c': {
        char *save_var = (char *)va_arg(argp, char *);
        *save_var = *line;
      } break;

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
