#include "./utils.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *file = fopen("./test_input.txt", "r");
  size_t read;

  char *left = NULL;
  char *right = NULL;
  char *blank = NULL;
  size_t line_len = 0;

  int index = 1;

  int index_sum = 0;
  while (read != -1) {
    getline(&left, &line_len, file);
    getline(&right, &line_len, file);
    read = getline(&blank, &line_len, file);

    if (compare_lines(new_list_str(left), new_list_str(right))) {
      index_sum += index;
    }
    index++;
  }

  printf(" index sum %d\n", index_sum);
  fclose(file);
}
