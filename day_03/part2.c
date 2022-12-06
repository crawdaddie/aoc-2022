#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void process_three_lines(void (*callback)(char *line0, char *line1, char *line2,
                                          int *score),
                         int *score) {
  FILE *file = fopen("./input.txt", "r");
  size_t read;

  char *line0 = NULL;
  char *line1 = NULL;
  char *line2 = NULL;
  size_t line_len = 0;
  while ((read = getline(&line0, &line_len, file)) != -1) {
    getline(&line1, &line_len, file);
    getline(&line2, &line_len, file);
    callback(line0, line1, line2, score);
  }

  fclose(file);
}

int char_to_alphabet_idx(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  }
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 26;
  }
  return 0;
}

uint64_t chars_to_hot_ones(char *line) {
  int char_idx;

  int i = 0;
  uint64_t items = 0;

  while (line[i] && line[i] != '\n') {
    char_idx = char_to_alphabet_idx(line[i]);
    items |= (1ull << char_idx);
    i++;
  }
  return items;
}

void cb(char *line0, char *line1, char *line2, int *score) {
  uint64_t items = chars_to_hot_ones(line0);
  items &= chars_to_hot_ones(line1);
  items &= chars_to_hot_ones(line2);
  // bitwise & to find repeated char in each line of group

  int log2 = 0;
  while (items >>= 1) {
    log2++; // get highest power of 2 to get index of remaining 1
  }

  *score += log2 + 1;
}

int main(int argc, char **argv) {
  int score = 0;
  process_three_lines(cb, &score);
  printf("%d\n", score);
  return 0;
}
