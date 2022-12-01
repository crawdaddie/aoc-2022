#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int max_int(const int a, const int b) {
  if (a > b) {
    return a;
  } return b;
}

void process_lines(int *max_calories, int *calories) {
  FILE *file;
  file = fopen("../input.txt", "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;

  while ((read = getline(&line, &line_len, file)) != -1) {
    int line_val = atoi(line);
    *calories += line_val;
    if (line_val == 0) {
      *max_calories = max_int(*max_calories, *calories);
      *calories = 0;
    }
  }

  *max_calories = max_int(*max_calories, *calories);
  *calories = 0;

  fclose(file);
}

int main(int argc, char **argv) {

  int max_calories = 0;
  int calories = 0;
  process_lines(&max_calories, &calories);
  printf("max calories: %d\n", max_calories);
  return 0;
}
