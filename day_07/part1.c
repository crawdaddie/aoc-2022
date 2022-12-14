#include "./fs.c"
#include "./khash.h"
#include <search.h>
#include <stdio.h>

int main(int argc, char **argv) {
  char input_file[] = "./test_input.txt";

  FILE *file = fopen(input_file, "r");
  size_t read;
  size_t line_len = 0;
  char *line = NULL;

  char *current_dir = calloc(sizeof(char), 32);

  kh_m32_t *fs = new_fs();
  khiter_t k;

  while ((read = getline(&line, &line_len, file)) != -1) {
    /* printf("current_dir: %s\n", current_dir); */

    if (line[0] == '$' && line[2] == 'c') {
      printf("%s\n", line);
      strcpy(current_dir, handle_cd(current_dir, parse_cd(line)));
      printf("changed to %s\n", current_dir);

      k = kh_get(m32, fs, current_dir);
      int ret, is_missing;
      is_missing = (k == kh_end(fs));

      if (is_missing) {
        printf("registering dir %s\n", current_dir);
        k = kh_put(m32, fs, current_dir,
                   &ret); // insert a key to the hash table
      }
      continue;
    }

    if (line[0] == '$' && line[2] == 'l') {
      continue;
    }

    if (line[0] == 'd') {
      continue;
    }

    int size = parse_filesize(line);
    int current_size = kh_value(fs, k);
    kh_value(fs, k) = current_size + size;
  }

  for (k = kh_begin(fs); k != kh_end(fs); ++k) {
    printf("key: %s val: %d\n", kh_key(fs, k), kh_val(fs, k));
  }

  kh_destroy(m32, fs);
  fclose(file);
  return 0;
}
