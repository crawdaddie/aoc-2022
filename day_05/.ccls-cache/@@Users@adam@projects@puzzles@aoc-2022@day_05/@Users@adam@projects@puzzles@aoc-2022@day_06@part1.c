#include "../common/debug.h"
#include <stdio.h>
#include <string.h>
typedef uint32_t u32;

int count_ones(u32 num) {
  /*Counting bits set, Brian Kernighan's way
   * https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
   * */
  int c; // c accumulates the total bits set in num
  for (c = 0; num; c++) {
    num &= num - 1; // clear the least significant bit set
  }
  return c;
}

int read_chars(char *input_file, int size) {
  FILE *file1 = fopen(input_file, "r");
  FILE *file2 = fopen(input_file, "r");
  char right, left;
  int index = 0;
  u32 bits = 0;
  while ((right = fgetc(file1)) != EOF) {
    bits ^= 1 << (right - 'a');

    if (index >= size) {
      left = fgetc(file2);
      bits ^= 1 << (left - 'a');
    }

    if (count_ones(bits) == size) {
      break;
    }

    index++;
  }
  fclose(file1);
  fclose(file2);
  return index + 1;
}

int main(int argc, char **argv) {
  int size = argc == 2 ? atoi(argv[1]) : 4;
  int start = read_chars("./input.txt", size);
  printf("%d\n", start);
  return 0;
}
