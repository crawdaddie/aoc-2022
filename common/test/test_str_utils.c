#include "../str_utils.h"
#include <stdio.h>

static const char *green_tick = "\033[92m✓\033[0m";
static const char *red_cross = "\033[93m✖\033[0m";

int test_parsef() {
  int arg0, arg1, arg2, arg3;
  parsef("%-%,%-%\n", "81-2,4-5\n", &arg0, &arg1, &arg2, &arg3);
  return arg0 == 81 && arg1 == 2 && arg2 == 4 && arg3 == 5;
}

int test_parsef_2() {
  int arg0, arg1, arg2, arg3;
  parsef("-%-%,%-%\n", "-81-2,4-502\n", &arg0, &arg1, &arg2, &arg3);
  return arg0 == 81 && arg1 == 2 && arg2 == 4 && arg3 == 502;
}

int test_parsef_day5() {
  int arg0, arg1, arg2;
  parsef("move % from % to %\n", "move 2 from 4 to 9\n", &arg0, &arg1, &arg2);
  return arg0 == 2 && arg1 == 4 && arg2 == 9;
}

int test_parsef_dyn() {
  int arg0, arg1, arg2;
  char *arg3;
  parsef_dyn("move %d from %d to %d %s\n", "move 21 from 4 to 9 please\n",
             &arg0, &arg1, &arg2, &arg3);
  printf("%d %d %d %s\n", arg0, arg1, arg2, arg3);

  return arg0 == 21 && arg1 == 4 && arg2 == 9 && strcmp(arg3, "please");
}

void run_test(char *name, int (*test_func)()) {
  if (!test_func()) {
    printf("%s %s failed\n", red_cross, name);
    return;
  }
  printf("%s %s passed\n", green_tick, name);
}

int main(int argc, char **argv) {
  run_test("day 4", test_parsef);
  run_test("test_parsef", test_parsef_2);
  run_test("test_parsef day 5", test_parsef_day5);
  run_test("test_parsef_dyn day 5", test_parsef_dyn);
  return 0;
}
