/* #include "./monkeys.h" */
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 20

#define P00_ISIT(WHAT, X, I) (X) WHAT
#define P99_ALLEQ(FIRST, ...)                                                  \
  P99_FOR(== (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

typedef int (*t_operation)(int worry);
typedef int (*t_pass)(int worry);
typedef struct q_int {
  int *items;
  int bottom;
  int top;
  t_operation operation;
  t_pass pass;

} q_int;

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

void queue_new(q_int *q) {
  q->top = 0;
  q->bottom = 0;
};

int queue_is_full(q_int *q) {
  /* if ((q->top + 10) - (q->bottom + QUEUE_MAX) == QUEUE_MAX - 1) { */
  /*   return 1; */
  /* } */
  return 0;
};
int queue_is_empty(q_int *q) {
  if (q->top == q->bottom) {
    return 1;
  }
  return 0;
};
void queue_push(q_int *q, int newitem) {
  if (queue_is_full(q)) {
    return;
  }
  q->items[q->top] = newitem;
  q->top = (q->top + 1) % QUEUE_MAX;
};
int queue_pop_left(q_int *q) {
  int popped_left = q->items[q->bottom];
  q->items[q->bottom] = 0;
  q->bottom = (q->bottom + 1) % QUEUE_MAX;
  return popped_left;
};

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

q_int *new_monkey(int *items, int num_items, t_operation operation,
                  t_pass pass) {

  q_int *monkey = calloc(sizeof(q_int), 1);
  monkey->items = calloc(sizeof(int), QUEUE_MAX);
  for (int i = 0; i < num_items; i++) {
    monkey->items[i] = items[i];
  }
  monkey->bottom = 0;
  monkey->top = num_items;
  monkey->operation = operation;
  monkey->pass = pass;

  return monkey;
}

int main(int argc, char **argv) {
  int items_0[2] = {79, 98};
  int items_1[4] = {54, 65, 75, 74};
  int items_2[3] = {79, 60, 97};
  int items_3[1] = {74};

  q_int *monkey_items[4] = {
      new_monkey(items_0, 2, monkey_0_operation, monkey_0_pass),
      new_monkey(items_1, 4, monkey_1_operation, monkey_1_pass),
      new_monkey(items_2, 3, monkey_2_operation, monkey_2_pass),
      new_monkey(items_3, 1, monkey_3_operation, monkey_3_pass),
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
