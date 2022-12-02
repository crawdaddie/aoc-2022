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
    return 1;

  case 'B':
  case 'Y':
    return 2;

  case 'C':
  case 'Z':
    return 3;
  }
}

void cb(char *line, int *score) {
  int op = mapping(line[0]);
  int you = mapping(line[2]);
  int result;
  if (you == op) {
    result = 3;
  } else {
    // does your choice beat op's?
    // 1 > 3
    // 2 > 1
    // 3 > 2
    result = 6 * (op == (((you - 1) > 0) ? you - 1 : 3));
  };
  *score += (you + result);
}

void cb_part2(char *line, int *score) {
  int op = mapping(line[0]);
  int you = mapping(line[2]);
  int result;

  switch (you) {
  case 2:
    // draw
    result = 3 + op;
    break;
  case 3:
    // you win
    result = 6 + ((op + 1) > 3 ? 1 : op + 1);
    break;
  case 1:
    // you lose
    result = ((op - 1) > 0 ? op - 1 : 3);
    break;
  }
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
