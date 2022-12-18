#include "../utils.h"

static const char *green_tick = "\033[92m✓\033[0m";
static const char *red_cross = "\033[93m✖\033[0m";

void assert(int condition, char *text) {
  if (condition == 1) {
    printf("%s %s is true\n", green_tick, text);
  } else {
    printf("%s %s is false\n", red_cross, text);
  }
}

int main(int argc, char **argv) {
  assert(compare_lines("1\n", "1\n", NULL, NULL) == 1, "digit 1");

  assert(compare_lines("1\n", "2\n", NULL, NULL) == 1, "digit 1 2");

  assert(compare_lines("2\n", "1\n", NULL, NULL) == 0, "digit 2 1");

  assert(compare_lines("[1,1,3]\n", "[1,1,5]\n", NULL, NULL) == 1,
         "digit [1,1,3], [1,1,5]");
  // pair 1 correct order
  //
  assert(compare_lines(new_list_str("[1,1,3,1,1]\n"), "[1,1,5,1,1]\n", NULL,
                       NULL) == 1,
         "inputs [1,1,3,1,1] & [1,1,5,1,1] are in the correct order");

  // pair 2 correct order
  assert(compare_lines("[[1],[2,3,4]]\n", "[[1],4]\n", NULL, NULL) == 1,
         "inputs [[1],[2,3,4]] & [[1],4] are in the correct order");

  // pair 3 incorrect order
  assert(compare_lines("[9]\n", "[[8,7,6]]\n", NULL, NULL) == 0,
         "inputs [9] & [[8,7,6]] are not in the correct order");

  // pair 4 incorrect order
  assert(compare_lines("[[4,4],4,4]\n", "[[4,4],4,4,4]\n", NULL, NULL) == 1,
         "inputs [[4,4],4,4] , [[4,4],4,4,4] are in correct order");

  assert(compare_lines("[7,7,7,7]\n", "[7,7,7]\n", NULL, NULL) == 0,
         "inputs [7,7,7,7] & [7,7,7] are not in correct order");

  assert(compare_lines("[]\n", "[3]\n", NULL, NULL) == 1,
         "inputs [] & [3] are in the correct order");

  assert(compare_lines("[[[]]]\n", "[[]]\n", NULL, NULL) == 0,
         "inputs [[[]]] & [[]] are not in the correct order");

  assert(compare_lines("[1,[2,[3,[4,[5,6,7]]]],8,9]\n",
                       "[1,[2,[3,[4,[5,6,0]]]],8,9]\n", NULL, NULL) == 0,
         "inputs [1,[2,[3,[4,[5,6,7]]]],8,9] & [1,[2,[3,[4,[5,6,0]]]],8,9] are"
         "not in the correct order");
}
