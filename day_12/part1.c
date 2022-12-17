#include "../common/input.h"
#include "../common/queue.h"
#include <stdio.h>


#ifdef TEST
#define ROWS 5
#define COLS 8
#endif
#ifndef TEST
#define ROWS 41
#define COLS 132
#endif

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
  int dist;
} pos;

QUEUE_TYPE(pos);

void populate_matrix(char *line, int i, int matrix[ROWS][COLS], pos *start,
                     pos *end) {
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

int pos_in_bounds(pos pos) {
  return pos.x >= 0 && pos.x < COLS && pos.y >= 0 && pos.y < ROWS;
}

int relative_height(pos p, pos neighbor, int matrix[ROWS][COLS]) {
  int p_height, n_height;
  p_height = matrix[p.y][p.x];
  n_height = matrix[neighbor.y][neighbor.x];
  return n_height - p_height;
}

static const pos dirs[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // U D L R
void enqueue_neighbors(pos start, pos end, int matrix[ROWS][COLS],
                       int visited[ROWS][COLS], t_q_pos *q) {

  for (int i = 0; i < 4; i++) {
    pos dir = dirs[i];

    pos neighbor = {start.x + dir.x, start.y + dir.y, start.dist + 1};

    if (!(visited[neighbor.y][neighbor.x]) && pos_in_bounds(neighbor) &&
        relative_height(start, neighbor, matrix) <= 1) {
      visited[neighbor.y][neighbor.x] = 1;
      q_pos_push(q, neighbor);
    }
  }
}

int main(int argc, char **argv) {
  int score = 0;
  int matrix[ROWS][COLS];
  pos start, end;
  WITH_INPUT_LINES("./input.txt", populate_matrix, matrix, &start, &end);
  t_q_pos *q = q_pos_new(&start, 1, ROWS * COLS);
  int visited[ROWS][COLS] = {0};
  while (!q_pos_is_empty(q)) {
    pos p = q_pos_pop_left(q);

    if (p.x == end.x && p.y == end.y) {
      printf("found end in %d steps\n", p.dist);
      break;
    }

    enqueue_neighbors(p, end, matrix, visited, q);
  }


  return 0;
}
