#include "../common/str_utils.h"
#include <stdio.h>

void cb(char *line) {

  if (line[0] == '$' && line[2] == 'c') {
    char *dirname;
    parsef_dyn("$ cd %s\n", line, &dirname);
    printf("cd to %s\n", dirname);
    return;
  }

  if (line[0] == '$' && line[2] == 'l') {
    return;
  }

  if (line[0] == 'd') {
    return;
  }
}

int main(int argc, char **argv) {
  char input_file[] = "./test_input.txt";

  FILE *file = fopen(input_file, "r");
  size_t read;
  size_t line_len = 0;
  char *line = NULL;

  while ((read = getline(&line, &line_len, file)) != -1) {
  }

  fclose(file);
  return 0;
}



