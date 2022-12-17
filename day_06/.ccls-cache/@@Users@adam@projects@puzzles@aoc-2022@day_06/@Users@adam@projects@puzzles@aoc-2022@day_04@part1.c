#include "../common/str_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_lines(void (*callback)(char *line, int line_len, int *score),
                int *score) {
  FILE *file = fopen("./input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  while ((read = getline(&line, &line_len, file)) != -1) {
    callback(line, read - 1, score);
  }

  fclose(file);
}

void cb(char *line, int len, int *score) {
  int min0, max0, min1, max1;
  parsef_int("%-%,%-%\n", line, &min0, &max0, &min1, &max1);

  if ((min0 >= min1 && max0 <= max1) || (min1 >= min0 && max1 <= max0)) {
    *score += 1;
  }
}

int main(int argc, char **argv) {
  int score = 0;
  read_lines(cb, &score);
  printf("your score part1: %d\n", score);
  return 0;
}
