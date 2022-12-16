#include "../common/input.h"
#include <stdio.h>

void process_lines(char *line, int i, int *score){

};

int main(int argc, char **argv) {

  char *input_file = "./input.txt";
  FILE *file = fopen(input_file, "r");
  size_t read;
  char *line1 = NULL;
  char *line2 = NULL;
  char *blank = NULL;
  size_t line_len = 0;

  while ((read = getline(&line1, &line_len, file)) != -1) {
    getline(&line2, &line_len, file);
    printf("line1: %sline2: %s\n", line1, line2);
    if (getline(&blank, &line_len, file) == -1) {
      break;
    };
  }
  fclose(file);
}
