#include <stdio.h>
#include "../common/debug.h"

typedef struct acc {
  int index;
  u_int32_t bits;
  u_int32_t trailing_bits;
} acc;

int read_chars(char *input_file,
                int (*callback)(char left, char right, int index, uint32_t *bits),
                acc *acc
                ) {
  FILE *file1 = fopen(input_file, "r");
  FILE *file2 = fopen(input_file, "r");
  char left = 0, right;
  int start = 0;
  int index = 0;
  uint32_t bits = 0;
  while ((right = fgetc(file1)) != EOF) {
    if (index > 3) {
      left = fgetc(file2);
    }
    if (right != '\n') {

      start = callback(left, right, index, &bits);
      if (start != -1) {
        break;
      }
    }
    index++;
  }
  fclose(file1);
  fclose(file2);
  return start;
}

  /* uint32_t char_bits = 1 << right_char; */
  /* acc->bits = acc->bits &(~acc->trailing_bits) | char_bits; */
  /*  */
  /*  */
  /*  */
  /* printf(acc->index < 10 ? " %d: " : "%d: ", acc->index); */
  /* print_bits_32(acc->bits); */
  /*  */
  /* printf("    "); */
  /* print_bits_32(acc->trailing_bits); */
  /*  */
  /* if (acc->index > 3) { */
  /*   acc->trailing_bits = char_bits; */
  /* } */

int cb(char left, char right, int index, uint32_t *bits) {
  uint32_t left_bits = left == 0 ? 0 : 1 << (left - '0' - 49);
  uint32_t right_bits = 1 << (right - '0' - 49);
  uint32_t trunc_bits = *bits | left_bits;
  uint32_t new_bits = trunc_bits | right_bits;
  *bits = new_bits;

  print_bits_32(trunc_bits);
  print_bits_32(right_bits);
  print_bits_32(new_bits);
  printf("\n");

  if (new_bits != trunc_bits) {
    return index;
  }
  return -1;
}

int main(int argc, char **argv) {
  acc acc = {.index = 0, .bits = 0, .trailing_bits = 0};
  int start = read_chars("./test_alpha.txt", cb, &acc);
  printf("%d\n", start);
  return 0;
}
