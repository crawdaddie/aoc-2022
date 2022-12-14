#include "../common/str_utils.h"
#include "./khash.h"
#include <stdio.h>
#include <string.h>
KHASH_MAP_INIT_STR(m32, int)

// khash_t(m32) *h = kh_init(m32);

// int ret, is_missing;
// khiter_t k;
// k = kh_put(m32, h, "/", &ret);
// kh_value(h, k) = 1;

// k = kh_get(m32, h, "/");
// is_missing = (k == kh_end(h));
// k = kh_get(m32, h, "/");
// kh_del(m32, h, k);
// kh_value(h, 2) = 2;
// for (k = kh_begin(h); k != kh_end(h); ++k) {
//   printf("hash: %d\n", kh_val(h, k));
// }
// kh_destroy(m32, h);

typedef struct dir {
  int file_sizes;
  char *name;
} dir;

khash_t(m32) * new_fs() { return kh_init(m32); }

dir *new_dir(dir *current_dir, char *name) {
  dir *new_dir = malloc(sizeof(dir));
  new_dir->file_sizes = 0;
  new_dir->name = name;
  return new_dir;
}

void register_dir(char *current_dir, dir *new_dir) {}
void handle_register_dir(char *current_dir, char *name) {}

char *parse_cd(char *line) {
  line[strcspn(line, "\n")] = 0;
  return line + 5;
}

char *handle_move_up_directory(char *current_dir) {
  int len = strlen(current_dir);
  int i;
  for (i = len; current_dir[i] != '/'; i--)
    ;
  char *new_string = calloc(sizeof(char), len - i);
  strncpy(new_string, current_dir, len - i);
  return new_string;
}
char *handle_cd(char *current_dir, char *dest) {
  if (strcmp(dest, "/") == 0) {
    return dest;
  }
  if (strcmp(current_dir, dest) == 0) {
    return current_dir;
  }
  if (strcmp(dest, "..") == 0) {
    return handle_move_up_directory(current_dir);
  }
  if (strcmp(current_dir, "/") == 0) {
    char *new_current_dir =
        calloc(sizeof(char), strlen(current_dir) + strlen(dest));
    sprintf(new_current_dir, "%s%s", current_dir, dest);
    return new_current_dir;
  }

  char *new_current_dir =
      calloc(sizeof(char), strlen(current_dir) + 1 + strlen(dest));
  sprintf(new_current_dir, "%s/%s", current_dir, dest);
  return new_current_dir;
}

char *parse_register_dir(char *line) {
  line[strcspn(line, "\n")] = 0;
  return line + 4;
}

int parse_filesize(char *line) {
  int size;
  char *filename;
  parsef("%d %s\n", line, &size, &filename);
  return size;
}
void handle_register_filesize(dir *current_dir, int size) {}
