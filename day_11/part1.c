#include "./monkeys.h"
#include <stdio.h>
void debug_matrix(q_int matrix[4]) {

  for (int i = 0; i < 4; i++) {
    printf("[");
    for (int j = 0; j < QUEUE_MAX; j++) {
      printf("%llu,", matrix[i].items[j]);
    }
    printf("] ");
    printf("%d %d\n", matrix[i].bottom, matrix[i].top);
  }
}

/* Monkey 0: */
/*   Starting items: 75, 63 */
/*   Operation: new = old * 3 */
/*   Test: divisible by 11 */
/*     If true: throw to monkey 7 */
/*     If false: throw to monkey 2 */
/*  */
MONKEY_ITEMS(monkey_0, P99_PROTECT({75, 63}));
MONKEY_OP(monkey_0, worry * 3);
MONKEY_PASS(monkey_0, 11, 7, 2);
MONKEY_CONSTRUCTOR(monkey_0);
/* Monkey 1: */
/*   Starting items: 65, 79, 98, 77, 56, 54, 83, 94 */
/*   Operation: new = old + 3 */
/*   Test: divisible by 2 */
/*     If true: throw to monkey 2 */
/*     If false: throw to monkey 0 */
/*  */
MONKEY_ITEMS(monkey_1, P99_PROTECT({65, 79, 98, 77, 56, 54, 83, 94}));
MONKEY_OP(monkey_1, worry + 3);
MONKEY_PASS(monkey_1, 2, 2, 0);
MONKEY_CONSTRUCTOR(monkey_1);
/* Monkey 2: */
/*   Starting items: 66 */
/*   Operation: new = old + 5 */
/*   Test: divisible by 5 */
/*     If true: throw to monkey 7 */
/*     If false: throw to monkey 5 */
/*  */

MONKEY_ITEMS(monkey_2, P99_PROTECT({66}));
MONKEY_OP(monkey_2, worry + 5)
MONKEY_PASS(monkey_2, 5, 7, 5);
MONKEY_CONSTRUCTOR(monkey_2);
/* Monkey 3: */
/*   Starting items: 51, 89, 90 */
/*   Operation: new = old * 19 */
/*   Test: divisible by 7 */
/*     If true: throw to monkey 6 */
/*     If false: throw to monkey 4 */
/*  */

MONKEY_ITEMS(monkey_3, P99_PROTECT({51, 89, 90}));
MONKEY_OP(monkey_3, worry * 19);
MONKEY_PASS(monkey_3, 7, 6, 4);
MONKEY_CONSTRUCTOR(monkey_3);

/* Monkey 4: */
/*   Starting items: 75, 94, 66, 90, 77, 82, 61 */
/*   Operation: new = old + 1 */
/*   Test: divisible by 17 */
/*     If true: throw to monkey 6 */
/*     If false: throw to monkey 1 */
/*  */
MONKEY_ITEMS(monkey_4, P99_PROTECT({75, 94, 66, 90, 77, 82, 61}));
MONKEY_OP(monkey_4, worry + 1)
MONKEY_PASS(monkey_4, 17, 6, 1);
MONKEY_CONSTRUCTOR(monkey_4);
/* Monkey 5: */
/*   Starting items: 53, 76, 59, 92, 95 */
/*   Operation: new = old + 2 */
/*   Test: divisible by 19 */
/*     If true: throw to monkey 4 */
/*     If false: throw to monkey 3 */
/*  */

MONKEY_ITEMS(monkey_5, P99_PROTECT({53, 76, 59, 92, 95}));
MONKEY_OP(monkey_5, worry + 2);
MONKEY_PASS(monkey_5, 19, 4, 3);
MONKEY_CONSTRUCTOR(monkey_5);
/* Monkey 6: */
/*   Starting items: 81, 61, 75, 89, 70, 92 */
/*   Operation: new = old * old */
/*   Test: divisible by 3 */
/*     If true: throw to monkey 0 */
/*     If false: throw to monkey 1 */
/*  */

MONKEY_ITEMS(monkey_6, P99_PROTECT({81, 61, 75, 89, 70, 92}));
MONKEY_OP(monkey_6, worry *worry);
MONKEY_PASS(monkey_6, 3, 0, 1);
MONKEY_CONSTRUCTOR(monkey_6);
/* Monkey 7: */
/*   Starting items: 81, 86, 62, 87 */
/*   Operation: new = old + 8 */
/*   Test: divisible by 13 */
/*     If true: throw to monkey 3 */
/*     If false: throw to monkey 5 */

MONKEY_ITEMS(monkey_7, P99_PROTECT({81, 86, 62, 87}));
MONKEY_OP(monkey_7, worry + 8);
MONKEY_PASS(monkey_7, 13, 3, 5);
MONKEY_CONSTRUCTOR(monkey_7);

/* #define PART_1 */

int inspect_items(q_int **monkeys, int idx) {
  q_int *monkey = monkeys[idx];

  int inspections = 0;
  while (!queue_is_empty(monkey)) {
    int worry = queue_pop_left(monkey);
    inspections++;
    worry = monkey->operation(worry);

#ifdef PART_1
    worry = worry / 3;
#endif

    queue_push(monkeys[monkey->pass(worry)], worry);
  }
  return inspections;
}
int main(int argc, char **argv) {
  q_int *monkey_items[8] = {
      monkey_0(), monkey_1(), monkey_2(), monkey_3(),
      monkey_4(), monkey_5(), monkey_6(), monkey_7(),

  };
  int inspections[8] = {0};

  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 8; j++) {
      inspections[j] += inspect_items(monkey_items, j);
    }
  }
  debug_matrix(*monkey_items);
  int monkey_business = 1;
  for (int k = 0; k < 8; k++) {
    printf("monkey %d inspected items %d times\n", k, inspections[k]);
    monkey_business *= inspections[k];
  }

  return 0;
}
