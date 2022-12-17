#include "./str_utils.h"

int test_parsef() {
  int val0, val1, val2, val3;
  parsef("%-%,%-%", "8-2,3-4", &val0, &val1, &val2, &val3);
  return val0 == 8 && val1 == 2 && val2 == 3 && val3 == 4;
}

int main(int argc, char **argv) {
  if (!test_parsef()) {
    return 1;
  }
  return 0;
}
