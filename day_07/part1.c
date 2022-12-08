#include "../common/str_utils.h"
#include <stdio.h>

typedef struct filesys {
  int file_sizes;
  struct filesys *subdirs;
} filesys;

int main(int argc, char **argv) {
  char input_file[] = "./test_input.txt";

  FILE *file = fopen(input_file, "r");
  size_t read;
  size_t line_len = 0;
  char *line = NULL;


  while ((read = getline(&line, &line_len, file)) != -1) {
    line[strcspn(line, "\n")] = 0;

    if (line[0] == '$' && line[2] == 'c') {
      char *dirname = line + 5;
      printf("cd to %s\n", dirname);
      continue;
    }

    if (line[0] == '$' && line[2] == 'l') {
      while ((read = getline(&line, &line_len, file)) != -1 && line[0] != '$')  {

        if (line[0] == 'd') {
          line[strcspn(line, "\n")] = 0;
          char *register_dir = line + 4;
          printf("register dir %s\n", register_dir);
        } else {
          int size;
          char *filename;
          parsef_dyn("%d %s\n", line, &size, &filename);
          filename[strcspn(filename, "\n")] = 0;
          printf("f: %d %s\n", size, filename);
        }
      } 
      continue;
    }

  }

  fclose(file);
  return 0;
}



