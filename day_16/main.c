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

void parse_line(char *line, int i, Valves *Valves) {
  char label[3];
  int flow_rate;
  sscanf(line, "Valve %c%c has flow rate=%d;", &label[0], &label[1],
         &flow_rate);

  int valve_index = parse_base_26(label);

  Valves->indices[i] = valve_index;
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
  Valves->nodes[valve_index] = node;
}

#define MAX 200
void floyd_warshall(Valves *Valves) {

  // Adding vertices individually

  int k, i, j;
  for (k = 0; k < NUM_VALVES; k++) {

    node valve = Valves->nodes[Valves->indices[k]];
    for (i = 0; i < valve.tunnels->length; i++) {
      int linked_valve_index = list_int_at(valve.tunnels, i);
      node linked_valve = Valves->nodes[linked_valve_index];
      Valves->distances[k][linked_valve.idx] = 1;
    }
  }

  for (k = 0; k < NUM_VALVES; k++) {
    for (i = 0; i < NUM_VALVES; i++) {
      for (j = 0; j < NUM_VALVES; j++) {
        if (Valves->distances[i][k] + Valves->distances[k][j] <
            Valves->distances[i][j]) {
          int dist =
              i == j ? 0 : Valves->distances[i][k] + Valves->distances[k][j];
          Valves->distances[i][j] = dist;
        }
      }
    }
  }
}
void debug_indices(int indices[NUM_VALVES]) {
  for (int i = 0; i < NUM_VALVES; i++) {
    printf("slot %d -> valve %03d\n", i, indices[i]);
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
  Valves Valves = {
      .nodes = {0},
      .indices = {0},
      .distances = {[0 ... NUM_VALVES - 1] = {[0 ... NUM_VALVES - 1] = MAX}}};

  WITH_INPUT_LINES(INPUT, parse_line, &Valves);
  floyd_warshall(&Valves);

  debug_valves(Valves.nodes, Valves.indices);
  debug_matrix(Valves.distances);
  debug_indices(Valves.indices);

  /* bfs_valves(valve_indices, valves); */

  return 0;
}
