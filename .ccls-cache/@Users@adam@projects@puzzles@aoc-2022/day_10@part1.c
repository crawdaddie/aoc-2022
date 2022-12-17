#include "../common/str_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_lines(char *input_file, int *score) {
  FILE *file = fopen(input_file, "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  int i = 1;
  int x = 1;
  while ((read = getline(&line, &line_len, file)) != -1) {
    if (*line == 'a') {
      int v;
      i++;
      if ((i - 20) % 40 == 0) {
        printf("%dth cycle: %d, sig strength: %d\n", i, x, i * x);
        *score += i * x;
      }
      parsef("addx %d\n", line, &v);
      x += v;

      i++;
      if ((i - 20) % 40 == 0) {
        printf("%dth cycle: %d, sig strength: %d\n", i, x, i * x);
        *score += i * x;
      }
      continue;
    }
    if (*line == 'n') {
      i++;
      if ((i - 20) % 40 == 0) {
        printf("%dth cycle: %d, sig strength: %d\n", i, x, i * x);
        *score += i * x;
      }
      continue;
    }
  }

  fclose(file);
}

int main(int argc, char **argv) {
  int score = 0;
  process_lines("./input.txt", &score);
  printf("your score part1: %d\n", score);
  return 0;
}
