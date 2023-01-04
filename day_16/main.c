#include "../common/input.h"
#include "../common/str_utils.h"
#include <stdbool.h>
bool is_prefix(const char *s, const char *pre) {
  return strncmp(pre, s, strlen(pre)) == 0;
}
void process_line(char *line, int i, void *s) {
  char label[3];
  int flow_rate;
  sscanf(line, "Valve %c%c has flow rate=%d;", &label[0], &label[1],
         &flow_rate);
  printf("%s %d\n", label, flow_rate);
  while (*line != ';') {
    line++;
  }
  line += 2;
  if (is_prefix(line, "tunnels")) {
    line += strlen("tunnels lead to valves ");
  } else {
    line += strlen("tunnel leads to valve ");
  }
  printf("%s\n", line);

  /* printf("valve '%s' rate %d\n", label, flow_rate); */
}

int main(int argc, char **argv) {
  void *s;

  WITH_INPUT_LINES("./test_input.txt", process_line, s);
  return 0;
}
