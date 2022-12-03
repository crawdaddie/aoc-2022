#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_lines(void (*callback)(char *line, int line_len, int *score),
                   int *score) {
  FILE *file = fopen("./input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  while ((read = getline(&line, &line_len, file)) != -1) {
    callback(line, read - 1, /* ignore newline char at end*/
             score);
  }

  fclose(file);
}
int char_to_alpha_num(char c) {
  int ascii = (int)c;
  if (ascii >= 65 && ascii <= 90) {
    return ascii - 38;
  }
  if (ascii >= 97 && ascii <= 122) {
    return ascii - 96;
  }
  return 0;
}

void cb(char *line, int len, int *score) {
  int items[52] = {0};
  int char_score;
  int i;

  for (i = 0; i < len / 2; i++) {
    char_score = char_to_alpha_num(line[i]);
    items[char_score - 1] = 1;
  }
  for (i = (len / 2); i < len; i++) {
    char_score = char_to_alpha_num(line[i]);
    if (items[char_score - 1]) {
      *score += char_score;
      items[char_score - 1] = 0;
    };
  }
}

int main(int argc, char **argv) {
  int score = 0;
  process_lines(cb, &score);
  printf("your score part1: %d\n", score);
  return 0;
}
