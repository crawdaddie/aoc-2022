#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void shift_array_down(int *array, int i) {
  /*
   * ([0,1,2,3], 2) -> [1,2,2,3]
   */
  for (int j = 0; j < i; j++) {
    array[j] = array[j + 1];
  }
}

void process_elf_calories(int *max_calories, int elf_calories) {

  if (elf_calories >= max_calories[0]) {
    for (int i = 2; i >= 0; i--) {
      if (elf_calories >= max_calories[i]) {
        shift_array_down(max_calories, i);
        max_calories[i] = elf_calories;
        break;
      }
    }
  }
}

void process_lines(int *max_calories) {
  FILE *file = fopen("../input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  int calories = 0;
  while ((read = getline(&line, &line_len, file)) != -1) {
    int line_val = atoi(line);
    calories += line_val;

    if (line_val == 0) {
      process_elf_calories(max_calories, calories);
      calories = 0;
    }
  }
  process_elf_calories(max_calories, calories);
  calories = 0;
  fclose(file);
}

int main(int argc, char **argv) {
  int max_calories[3] = {0, 0, 0};

  process_lines(max_calories);
  printf("top 3 calories: %d %d %d\n", max_calories[0], max_calories[1],
         max_calories[2]);
  printf("sum of top 3 elf calories %d\n",
         max_calories[0] + max_calories[1] + max_calories[2]);
  return 0;
}
