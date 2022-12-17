#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5
/*  */
// #define ROWS 99
// #define COLS 99

void debug_matrix(int matrix[ROWS][COLS]) {

  for (int i = 0; i < ROWS; i++) {
    printf("[");
    for (int j = 0; j < COLS; j++) {
      printf("%d,", matrix[i][j]);
    }
    printf("]\n");
  }
}

typedef struct last_highest_tree {
  int value;
  int idx;
} LHT;

void check_visibility(LHT *hlv, int input, int idx) {
  if (input > hlv->value) {
    hlv->value = input;
    hlv->idx = idx;
  }
}

int parse_tree_height(char *line, int i) { return line[i] - '0'; }

int get_visibility(int idx, int val, int edge_idx, LHT blocker) {
  if (idx == 3) {
    printf("val %d idx %d %d %d\n", val, idx, blocker.value, blocker.idx);
  }
  /* return 1; */
  if (val > blocker.value) {
    return abs(idx - 1 - edge_idx); // unobstructed view back towards edge
  }
  return abs(idx - 1 - blocker.idx);
}

int main(int argc, char **argv) {

  FILE *file = fopen("./test_input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;

  int trees[ROWS][COLS];
  int scenic_scores[ROWS][COLS] = {[0 ... 4] = {[0 ... 4] = 1}};
  debug_matrix(scenic_scores);

  for (int row = 0; (read = getline(&line, &line_len, file)) != -1; row++) {
    int num_cols = read - 1;
    int last_idx = num_cols - 1;
    LHT hlv_l = {-1, 0};
    LHT hlv_r = {-1, last_idx};

    int l, r;

    for (int col = 0; col < read - 1; col++) {
      int l = parse_tree_height(line, col);
      int idx = col;
      trees[row][idx] = l;

      int visibility = get_visibility(idx, l, 0, hlv_l);
      scenic_scores[row][idx] *= visibility;
      if (row == 2 && idx == 3) {
        printf("[%d %d] %d %d\n", row, idx, visibility, hlv_l.idx);
      }
      check_visibility(&hlv_l, l, idx);

      idx = last_idx - row;

      int r = parse_tree_height(line, idx);

      visibility = get_visibility(col, r, last_idx, hlv_r);

      if (row == 2 && idx == 3) {
        printf("[%d %d] %d %d\n", row, idx, visibility, hlv_r.idx);
      }
      scenic_scores[row][idx] *= visibility;
      check_visibility(&hlv_r, r, col);
    }
  }

  int max_scenic_score;
  for (int col = 0; col < COLS; col++) {
    int last_idx = ROWS - 1;
    LHT hlv_l = {-1, 0};
    LHT hlv_r = {-1, last_idx};
    int l, r;

    for (int row = 0; row < ROWS; row++) {
      int idx = row;

      l = trees[idx][col];
      int visibility = get_visibility(idx, l, 0, hlv_l);

      if (idx == 2 && col == 3) {
        printf("[%d %d] %d %d\n", idx, col, visibility, hlv_l.idx);
      }
      scenic_scores[idx][col] *= visibility;
      check_visibility(&hlv_l, l, idx);

      idx = last_idx - row;

      r = trees[idx][col];
      visibility = get_visibility(row, r, last_idx, hlv_r);

      if (idx == 2 && col == 3) {
        printf("[%d %d] %d %d\n", idx, col, visibility, hlv_r.idx);
      }

      scenic_scores[idx][col] *= visibility;
      check_visibility(&hlv_r, r, row);
    }
  }
  debug_matrix(scenic_scores);
  /* printf("score %d\n", score); */

  fclose(file);
  return 0;
}
