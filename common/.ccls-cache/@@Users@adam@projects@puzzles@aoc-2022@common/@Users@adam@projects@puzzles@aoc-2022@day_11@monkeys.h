#include <stdlib.h>

typedef int (*t_operation)(void *monkey, int worry);
typedef int (*t_test)(void *monkey, int item);

typedef struct item {
  int val;
  struct item *next;
} t_item;

typedef struct monkey {
  t_item *items;
  t_item *last_item;
  int inspections;
} monkey;

void add_item(monkey *monkey, t_item *item);
int perform_monkey_0(monkey **monkeys);
int perform_monkey_1(monkey **monkeys);
int perform_monkey_2(monkey **monkeys);
int perform_monkey_3(monkey **monkeys);
