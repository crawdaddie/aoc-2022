#include "../common/str_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_sprite(int cycle, int x) {
  int pixel = cycle % 40;
  if (pixel == 0) {
    printf("\n");
  }
  if (pixel >= x - 1 && pixel <= x + 1) {
    printf("\033[93m#\033[0m");
  } else {
    printf(".");
  }
}

int get_instruction(char *line) {
  if (*line == 'a') {
    int v;
    parsef_dyn("addx %d\n", line, &v);
    return v;
  }
  return 0;
}

int main(int argc, char **argv) {
  FILE *file = fopen("./input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;

  int timer = 0;
  int instruction = 0;
  int x = 1;

  for (int cycle = 0; cycle < 240; cycle++) {
    if (timer == 0) {
      x += instruction;
      read = getline(&line, &line_len, file);
      if (read != -1) {
        instruction = get_instruction(line);
        if (instruction != 0) {
          timer = 2;
        } else {
          timer = 1;
        }
      }
    }

    timer--;
    render_sprite(cycle, x);
  }

  fclose(file);
  return 0;
}
