#include "../common/input.h"
#include <stdio.h>

#define ROWS 41
#define COLS 132


void debug_matrix(int matrix[ROWS][COLS]) {

  for (int i = 0; i < ROWS; i++) {
    printf("[");
    for (int j = 0; j < COLS; j++) {
      printf("%d,", matrix[i][j]);
    }
    printf("]\n");
  }
}
typedef struct pos {
  int x;
  int y;
} pos;

void callback(char *line, int i, int matrix[41][132], pos *start, pos *end) {
  int j = 0;
  int val;
  while (*line != '\n') {
    if (*line == 'S') {
      val = 0;
      matrix[i][j] = val;
      start->x = j;
      start->y = i;
      line++;
      j++;
      continue;
    } 
    if (*line == 'E') {
      val = 25;
      matrix[i][j] = val;
      end->x = j;
      end->y = i;
      line++;
      j++;
      continue;
    }
    val = *line - 'a';
    matrix[i][j] = val;
    line++;
    j++;
  }
}



int main(int argc, char **argv) {
  int score = 0;
  int matrix[41][132];
  pos start, end;
  WITH_INPUT("./input.txt", callback, matrix, &start, &end);
  printf("start %d %d\n", start.x, start.y);
  printf("end %d %d\n", end.x, end.y);

  /* debug_matrix(matrix); */

  return 0;
}
