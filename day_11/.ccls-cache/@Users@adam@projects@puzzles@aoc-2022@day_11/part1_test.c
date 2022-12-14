/* #include "./monkeys.h" */
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 10

typedef int (*t_operation)(int worry);
typedef int (*t_pass)(int worry);

void debug_matrix(q_int matrix[4]) {

  for (int i = 0; i < 4; i++) {
    printf("[");
    for (int j = 0; j < QUEUE_MAX; j++) {
      printf("%d,", matrix[i].items[j]);
    }
    printf("] ");
    printf("%d %d\n", matrix[i].bottom, matrix[i].top);
  }
}

int perform_monkey(q_int **monkeys, int idx) {
  q_int *monkey = monkeys[idx];

  int inspections = 0;
  while (!queue_is_empty(monkey)) {
    int worry = queue_pop_left(monkey);
    inspections++;
    worry = monkey->operation(worry);
    worry = worry / 3;
    queue_push(monkeys[monkey->pass(worry)], worry);
  }
  return inspections;
}

int monkey_0_operation(int worry) { return worry * 19; }
int monkey_0_pass(int worry) {
  if (worry % 23 == 0) {
    return 2;
  }
  return 3;
}
int monkey_1_operation(int worry) { return worry + 6; }

int monkey_1_pass(int worry) {
  if (worry % 19 == 0) {
    return 2;
  }
  return 0;
}
int monkey_2_operation(int worry) { return worry * worry; }

int monkey_2_pass(int worry) {
  if (worry % 13 == 0) {
    return 1;
  }
  return 3;
}
int monkey_3_operation(int worry) { return worry + 3; }

int monkey_3_pass(int worry) {
  if (worry % 17 == 0) {
    return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  MONKEY_ITEMS(items_0, P99_PROTECT({79, 98}));
  MONKEY_ITEMS(items_1, P99_PROTECT({54, 65, 75, 74}));
  MONKEY_ITEMS(items_2, P99_PROTECT({79, 60, 97}));
  MONKEY_ITEMS(items_3, P99_PROTECT({74}));

  q_int *monkey_items[4] = {
      new_monkey(items_0, items_0_length, monkey_0_operation, monkey_0_pass),
      new_monkey(items_1, items_1_length, monkey_1_operation, monkey_1_pass),
      new_monkey(items_2, items_2_length, monkey_2_operation, monkey_2_pass),
      new_monkey(items_3, items_3_length, monkey_3_operation, monkey_3_pass),
  };
  int inspections[4] = {0};

  for (int i = 0; i < 4; i++) {
    printf("monkey %d inspected items %d times\n", i, inspections[i]);
  }

  for (int i = 0; i < 20; i++) {
    inspections[0] += perform_monkey(monkey_items, 0);
    inspections[1] += perform_monkey(monkey_items, 1);
    inspections[2] += perform_monkey(monkey_items, 2);
    inspections[3] += perform_monkey(monkey_items, 3);
  }

  debug_matrix(*monkey_items);
  for (int i = 0; i < 4; i++) {
    printf("monkey %d inspected items %d times\n", i, inspections[i]);
  }

  return 0;
}
