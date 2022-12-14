#include "../common/stack.h"
#include "../common/str_utils.h"
/*  */
/* #define ROWS 5 */
/* #define COLS 5 */
/*  */
#define ROWS 99
#define COLS 99

void debug_matrix(int matrix[ROWS][COLS]) {

  for (int i = 0; i < ROWS; i++) {
    printf("[");
    for (int j = 0; j < COLS; j++) {
      printf("%d,", matrix[i][j]);
    }
    printf("]\n");
  }
}

int check_visibility(int *hlv, int input, int row, int col,
                     int vis[ROWS][COLS]) {
  if (input > *hlv) {
    *hlv = input;
    return 1;
  }
  return 0;
}

void read_tree_height(int *hlv, int val, int row, int col, int vis[ROWS][COLS],
                      int trees[ROWS][COLS], int *score) {
  if (check_visibility(hlv, val, row, col, vis)) {
    if (vis[row][col] != 1) {
      vis[row][col] = 1;
      *score = *score + 1;
    }
  };
}

int parse_tree_height(char *line, int i) { return line[i] - '0'; }

int main(int argc, char **argv) {

  FILE *file = fopen("./input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;

  int trees[ROWS][COLS];
  int vis[ROWS][COLS] = {0};

  int row = 0;
  int score = 0;
  int hlv_l, hlv_r;
  while ((read = getline(&line, &line_len, file)) != -1) {
    hlv_l = -1;
    hlv_r = -1;

    int num_cols = read - 1;
    int last_idx = num_cols - 1;
    int l, r;
    for (int j = 0; j < read - 1; j++) {
      int l = parse_tree_height(line, j);
      int r = parse_tree_height(line, last_idx - j);
      trees[row][j] = l;

      read_tree_height(&hlv_l, l, row, j, vis, trees, &score);
      read_tree_height(&hlv_r, r, row, last_idx - j, vis, trees, &score);
    }
    row++;
  }

  for (int col = 0; col < COLS; col++) {
    hlv_l = -1;
    hlv_r = -1;
    int last_idx = ROWS - 1;

    for (int row = 0; row < ROWS; row++) {

      int l = trees[row][col];
      int r = trees[last_idx - row][col];

      read_tree_height(&hlv_l, l, row, col, vis, trees, &score);
      read_tree_height(&hlv_r, r, last_idx - row, col, vis, trees, &score);
    }
  }
  printf("score %d\n", score);

  fclose(file);
  return 0;
}
