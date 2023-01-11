#include "./debug.h"

void print_bits_64(uint64_t bits) {
  int b[64] = {0};
  int i;
  for (i = 0; bits > 0; i++) {
    b[i] = (int)(bits % 2);
    bits = bits / 2;
  }

  for (i = 0; i < 64; i++) {
    printf("%d", b[i]);
  };
  printf("\n");
}
void print_bits_32(uint32_t bits) {
  int b[32] = {0};
  int i;
  for (i = 0; bits > 0; i++) {
    b[i] = (int)(bits % 2);
    bits = bits / 2;
  }

  for (i = 0; i < 32; i++) {
    printf("%d", b[i]);
  };
  printf("\n");
}

void print_bits_16(uint16_t bits) {
  int b[16] = {0};
  int i;
  for (i = 0; bits > 0; i++) {
    b[i] = (int)(bits % 2);
    bits = bits / 2;
  }

  for (i = 0; i < 16; i++) {
    printf("%d", b[i]);
  };
  printf("\n");
}
