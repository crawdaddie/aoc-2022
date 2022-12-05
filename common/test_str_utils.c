#include "./str_utils.h"
#include <stdio.h>

static const char * green_tick = "\033[92m✓\033[0m";
static const char * red_cross = "\033[93m✖\033[0m";

int test_parsef() {
  int arg0, arg1, arg2, arg3;
  parsef("%-%,%-%\n","81-2,4-5\n",&arg0, &arg1, &arg2, &arg3);
  return arg0 == 81 && arg1 == 2 && arg2 == 4 && arg3 ==5;
}

int test_parsef_2() {
  int arg0, arg1, arg2, arg3;
  parsef("-%-%,%-%\n","-81-2,4-502\n", &arg0, &arg1, &arg2, &arg3);
  return arg0 == 81 && arg1 == 2 && arg2 == 4 && arg3 == 502;
}

int test_parsef_day5() {
  int arg0, arg1, arg2;
  parsef("move % from % to %\n","move 2 from 4 to 9\n",&arg0, &arg1, &arg2);
  return arg0 == 2 && arg1 == 4 && arg2 == 9;
}

int main(int argc, char **argv) {
  if (!test_parsef()) {
    printf("%s test_parsef failed\n", red_cross);
    return 1;
  };
  printf("%s test_parsef passed\n", green_tick);

  if (!test_parsef_2()) {
    printf("%s test_parsef_2 failed\n", red_cross);
    return 1;
  };
  printf("%s test_parsef_2 passed\n", green_tick);

  if (!test_parsef_day5()) {
    printf("%s test_parsef_day5 failed\n", red_cross);
    return 1;
  };

  printf("%s test_parsef_day5 passed\n", green_tick);

  return 0;

}
