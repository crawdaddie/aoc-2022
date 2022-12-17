//
//     [P]                 [C] [C]
//     [W]         [B]     [G] [V] [V]
//     [V]         [T] [Z] [J] [T] [S]
//     [D] [L]     [Q] [F] [Z] [W] [R]
//     [C] [N] [R] [H] [L] [Q] [F] [G]
// [F] [M] [Z] [H] [G] [W] [L] [R] [H]
// [R] [H] [M] [C] [P] [C] [V] [N] [W]
// [W] [T] [P] [J] [C] [G] [W] [P] [J]
//  1   2   3   4   5   6   7   8   9
//
//
//
//
//     [D]
// [N] [C]
// [Z] [M] [P]
//  1   2   3
//
// move 1 from 2 to 1
// move 3 from 1 to 3
// move 2 from 2 to 1
// move 1 from 1 to 2
//
#include "../common/stack.h"
#include "../common/str_utils.h"

void read_lines(char *input_file,
                void (*callback)(char *line, t_stack *stacks, int num_stacks),
                t_stack *stacks, int num_stacks) {
  FILE *file = fopen(input_file, "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  while ((read = getline(&line, &line_len, file)) != -1) {
    callback(line, stacks, num_stacks);
  }

  fclose(file);
}

void cb(char *line, t_stack *stacks, int num_stacks) {
  int num_crates, st_from, st_to;
  parsef("move % from % to %\n", line, &num_crates, &st_from, &st_to);

  st_from--;
  st_to--;

  char crates[num_crates];
  int i = 0;
  for (i = 0; i < num_crates; i++) {
    crates[i] = stack_pop(&stacks[st_from]);
  };
  for (i = num_crates - 1; i >= 0; i--) {
    stack_push(&stacks[st_to], crates[i]);
  }
}

int main(int argc, char **argv) {

  t_stack stacks[9] = {
      {"FRW", 2},      {"THMCDVWP", 7}, {"PMZNL", 4},
      {"JCHR", 3},     {"CPGHQTB", 6},  {"GCWLFZ", 5},
      {"WVLQZJGC", 7}, {"PNRFWTVC", 7}, {"JWHGRSV", 6},
  };

  read_lines("./input.txt", cb, stacks, 9);

  for (int i = 0; i < 9; i++) {
    t_stack st = stacks[i];
    char st_head = st.items[st.top];
    printf("%c", st_head);
  };
  printf("\n");

  return 0;
}
