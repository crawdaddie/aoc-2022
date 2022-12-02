#include <stdio.h>
#include <stdlib.h>

void process_lines(void (*callback)(char *line, int *score), int *score) {
  FILE *file = fopen("./input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  while ((read = getline(&line, &line_len, file)) != -1) {
    callback(line, score);
  }

  fclose(file);
}

int mapping(char c) {
  switch (c) {
  case 'A':
  case 'X':
    return 0;

  case 'B':
  case 'Y':
    return 1;

  case 'C':
  case 'Z':
    return 2;
  }
}

void cb(char *line, int *score) {
  int op = mapping(line[0]);
  int you = mapping(line[2]);
  int result = (you - op + 1 + 3) % 3; // 0->loss, 1->draw, 2->win
  *score += (you + 1 + result * 3);
}

void cb_part2(char *line, int *score) {
  int op = mapping(line[0]);
  int match_result = mapping(line[2]);
  int throw = ((op + match_result - 1) + 3) % 3; // 0->rock, 1->paper, 2->scissors
  int result = match_result * 3 + throw + 1;
  *score += result;
}

int main(int argc, char **argv) {
  int score = 0;
  process_lines(cb, &score);
  printf("your score part1: %d\n", score);
  score = 0;
  process_lines(cb_part2, &score);
  printf("your score part2: %d\n", score);
  return 0;
}
