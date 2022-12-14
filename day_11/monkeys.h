#ifndef _MONKEYS_H
#define _MONKEYS_H
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t Int;
#define QUEUE_MAX 36
#define LCM 9699690
typedef Int (*t_operation)(int worry);
typedef Int (*t_pass)(int worry);


typedef struct q_int {
  Int *items;
  int bottom;
  int top;
  t_operation operation;
  t_pass pass;

} q_int;

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
void queue_push(q_int *q, Int newitem) {
  if (queue_is_full(q)) {
    return;
  }
  q->items[q->top] = newitem;
  q->top = (q->top + 1) % QUEUE_MAX;
};
Int queue_pop_left(q_int *q) {
  Int popped_left = q->items[q->bottom];
  q->items[q->bottom] = 0;
  q->bottom = (q->bottom + 1) % QUEUE_MAX;
  return popped_left;
};

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(int))
// declare an array together with a variable containing the array's length
#define MONKEY_ITEMS(name, arr)                                                \
  static const int name##_items[] = arr;                                       \
  static size_t const name##_length = ARRAY_LENGTH(name##_items);

#define P99_PROTECT(...) __VA_ARGS__

#define MONKEY_OP(name, ...)                                                   \
  Int name##_operation(Int worry) { return __VA_ARGS__; }

#define MONKEY_PASS(name, test, t, f)                                          \
  int name##_pass(Int worry) {                                                 \
    if (worry % test == 0) {                                                   \
      return t;                                                                \
    }                                                                          \
    return f;                                                                  \
  };

q_int *new_monkey(int *items, int num_items, t_operation operation,
                  t_pass pass) {

  q_int *monkey = (q_int *)calloc(sizeof(q_int), 1);
  monkey->items = (Int *)calloc(sizeof(Int), QUEUE_MAX);
  for (int i = 0; i < num_items; i++) {
    monkey->items[i] = items[i];
  }
  monkey->bottom = 0;
  monkey->top = num_items;
  monkey->operation = operation;
  monkey->pass = pass;

  return monkey;
}

#define MONKEY_CONSTRUCTOR(name)                                               \
  q_int *name() {                                                              \
    return new_monkey(name##_items, name##_length, name##_operation,           \
                      name##_pass);                                            \
  }

#endif
