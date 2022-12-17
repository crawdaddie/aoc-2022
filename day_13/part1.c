#include <stdio.h>

int compare_lines(char *left, char *right) {
  return 1;
}

int main(int argc, char **argv) {

  FILE *file = fopen("./input.txt", "r");
  size_t read;

  char *left = NULL;
  char *right = NULL;
  char *blank = NULL;
  size_t line_len = 0;

  int index = 1;
  int index_sum = 0;
  while(read != -1) {
    read = getline(&left, &line_len, file);
    read = getline(&right, &line_len, file);
    read = getline(&blank, &line_len, file);
    if (compare_lines(left, right)) {
      index_sum += index;
    }
    index++;
  }
  printf("index sum %d\n", index_sum);
  fclose(file);

}
