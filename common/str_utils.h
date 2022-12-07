#ifndef _STR_UTILS
#define _STR_UTILS
#include <stdarg.h>
#include <stdio.h>

void parsef(char *tpl, char *line, ...);
void parsef_dyn(char *tpl, char *line, ...);
#endif
