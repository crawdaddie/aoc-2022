#ifndef _STR_UTILS
#define _STR_UTILS
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parsef_int(char *tpl, char *line, ...);
void parsef(char *tpl, char *line, ...);

void parse_int_n(char **line, char *stopchars, int num_stopchars, int *val);
#endif
