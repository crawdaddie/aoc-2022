#include "../common/input.h"
#include "../common/str_utils.h"
#include "./const.h"
#include "./valve_utils.c"
#include <stdbool.h>

bool is_prefix(const char *s, const char *pre) {
  return strncmp(pre, s, strlen(pre)) == 0;
}

int parse_base_26(char *val) { return (26 * (val[0] - 'A')) + (val[1] - 'A'); }
int max(int a, int b) { return a > b ? a : b; }
void parse_line(char *line, int i, node valves[ALPHA_CHARS], int *max_release,
                int *valve_indices) {
  char label[3];
  int flow_rate;
  sscanf(line, "Valve %c%c has flow rate=%d;", &label[0], &label[1],
         &flow_rate);

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

void floyd_warshall(int matrix[ALPHA_CHARS][ALPHA_CHARS]) {

  // Adding vertices individually
  int k, i, j;
  for (k = 0; k < ALPHA_CHARS; k++) {
    for (i = 0; i < ALPHA_CHARS; i++) {
      for (j = 0; j < ALPHA_CHARS; j++) {
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
  debug_valves(valves, valve_indices);

  printf("start %d, max %d\n", start, max_release);
  bfs_valves(valve_indices, valves);

  return 0;
}
