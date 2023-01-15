#include "../common/input.h"
#include "../common/str_utils.h"
#include "./const.h"
#include "./valve_utils.c"
#include <stdbool.h>

bool is_prefix(const char *s, const char *pre) {
  return strncmp(pre, s, strlen(pre)) == 0;
}

void debug_matrix(int matrix[NUM_VALVES][NUM_VALVES]) {

  for (int i = 0; i < NUM_VALVES; i++) {
    printf("[");
    for (int j = 0; j < NUM_VALVES; j++) {
      printf("%d,", matrix[i][j]);
    }
    printf("]\n");
  }
}

int parse_base_26(char *val) { return (26 * (val[0] - 'A')) + (val[1] - 'A'); }
int max(int a, int b) { return a > b ? a : b; }
void parse_line(char *line, int i, node valves[ALPHA_CHARS], int *max_release,
                int *valve_indices) {
  char label[3];
  int flow_rate;
  sscanf(line, "Valve %c%c has flow rate=%d;", &label[0], &label[1],
         &flow_rate);
  *max_release += flow_rate;

  int valve_index = parse_base_26(label);

  valve_indices[i] = valve_index;
  node node = new_node(flow_rate, i);

  while (*line != ';') {
    line++;
  }
  line += 2;

  if (is_prefix(line, "tunnels")) {
    line += strlen("tunnels lead to valves ");
  } else {
    line += strlen("tunnel leads to valve ");
  }

  while (line) {
    char *tok = strsep(&line, ", ");
    if (*tok != '\0') {
      int linked_valve_index = parse_base_26(tok);
      add_tunnel(&node, linked_valve_index);
    };
  }
  valves[valve_index] = node;
}

#define MAX 200
void floyd_warshall(int matrix[NUM_VALVES][NUM_VALVES],
                    node valves[ALPHA_CHARS * ALPHA_CHARS],
                    int valve_indices[NUM_VALVES], int max_release) {

  // Adding vertices individually

  int k, i, j;
  for (k = 0; k < NUM_VALVES; k++) {

    node valve = valves[valve_indices[k]];
    for (i = 0; i < valve.tunnels->length; i++) {
      int linked_valve_index = list_int_at(valve.tunnels, i);
      node linked_valve = valves[linked_valve_index];
      matrix[k][linked_valve.idx] = max_release - linked_valve.flow_rate;
    }
  }

  for (k = 0; k < NUM_VALVES; k++) {
    for (i = 0; i < NUM_VALVES; i++) {
      for (j = 0; j < NUM_VALVES; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
    }
  }
}

int open(int valves_open[NUM_VALVES], int vidx) {
  for (int i = 0; i < NUM_VALVES; i++) {
    if (vidx == i) {
      return i;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  node valves[ALPHA_CHARS * ALPHA_CHARS] = {0};
  int start = parse_base_26("AA");
  int max_release = 0;

  int valve_indices[NUM_VALVES];

  WITH_INPUT_LINES(INPUT, parse_line, valves, &max_release, valve_indices);
  /* max_release *= 30; */
  printf("max release %d\n", max_release);
  debug_valves(valves, valve_indices);

  int matrix[NUM_VALVES * NUM_VALVES] = {[0 ... NUM_VALVES * NUM_VALVES - 1] =
                                             MAX};
  floyd_warshall(matrix, valves, valve_indices, MAX);
  debug_matrix(matrix);

  /* bfs_valves(valve_indices, valves); */

  return 0;
}
