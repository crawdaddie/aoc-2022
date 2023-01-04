#include "../common/input.h"

#include "../common/str_utils.h"
#include <assert.h>

#include <stdlib.h>
#include <string.h>

#define ROWS 500
#define COLS 600

void debug_matrix(int matrix[ROWS][COLS], int startx) {

  for (int i = 0; i < ROWS; i++) {
    /* printf("["); */
    for (int j = startx; j < COLS; j++) {
      if (matrix[i][j] == 2) {
        printf("o");
      } else if (matrix[i][j] == 1) {
        printf("#");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

void order_pair(int *a, int *b) {
  if (*a > *b) {
    int a_val = *a;
    *a = *b;
    *b = a_val;
    printf("swapped pair %d %d\n", *a, *b);
  }
}

void populate_matrix(int x1, int y1, int x2, int y2, int matrix[ROWS][COLS]) {
  printf("draw (%d %d) -> (%d %d)\n", x1, y1, x2, y2);
  if (x1 == x2) {
    // vertical rock path
    order_pair(&y1, &y2);

    for (int i = y1; i <= y2; i++) {
      matrix[i][x1] = 1;
    }

    return;
  }
  if (y1 == y2) {
    // horizontal rock path
    order_pair(&x1, &x2);

    for (int i = x1; i <= x2; i++) {
      matrix[y1][i] = 1;
    }

    return;
  }
}

void read_line(char line[], int i, int matrix[ROWS][COLS], int *lowest_rock) {
  char *comma_split = ",";
  char *arrow_split = " -> ";
  char *token;
  char *coord;
  int x = 0, y = 0;

  while ((token = strsep(&line, arrow_split)) != NULL) {
    if (*token == '\0') {
      continue;
    }
    int _x = atoi(strsep(&token, comma_split));
    int _y = atoi(token);
    if (x != 0 && y != 0) {
      populate_matrix(x, y, _x, _y, matrix);
    }
    x = _x;
    y = _y;
    if (y >= *lowest_rock) {
      *lowest_rock = y;
    }
  }
}

void set_dir(int pos[2], int dir[2], const int matrix[ROWS][COLS]) {
  if (matrix[pos[1] + 1][pos[0]] == 0) {
    dir[1] = 1;
    dir[0] = 0;
    return;
  }
  if (matrix[pos[1] + 1][pos[0] - 1] == 0) {
    dir[1] = 1;
    dir[0] = -1;
    return;
  }

  if (matrix[pos[1] + 1][pos[0] + 1] == 0) {
    dir[1] = 1;
    dir[0] = 1;
    return;
  }
  dir[0] = 0;
  dir[1] = 0;
  return;
}

void sand_flow(int matrix[ROWS][COLS], int lowest_rock) {
  int pos[2] = {500, 0};
  int dir[2] = {0, 0};
  set_dir(pos, dir, matrix);
  while (!(dir[0] == 0 && dir[1] == 0) && pos[1] < (lowest_rock + 1)) {
    pos[0] += dir[0];
    pos[1] += dir[1];
    set_dir(pos, dir, matrix);
  }
  matrix[pos[1]][pos[0]] = 2;
}

int main(int argc, char **argv) {
  int matrix[ROWS][COLS] = {[0 ... ROWS - 1] = {[0 ... COLS - 1] = 0}};
  int lowest_rock = 0;
  WITH_INPUT_LINES("./input.txt", read_line, matrix, &lowest_rock);
  printf("lowest: %d\n", lowest_rock);
  int grains = 0;
  while (!matrix[0][500]) {
    sand_flow(matrix, lowest_rock);
    grains++;
  }
  debug_matrix(matrix, 490);
  printf("grains: %d\n", grains);

  return 0;
}
