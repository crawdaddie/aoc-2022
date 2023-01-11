#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 64
typedef struct q_int {
  int *items;
  int top;
  int bottom;
  int max;
} q_int;

void queue_new(q_int *q);
int queue_is_full(q_int *q);
int queue_is_empty(q_int *q);
void queue_push(q_int *q, int newitem);
char queue_pop_left(q_int *q);

#define QUEUE_TYPE(type)                                                       \
  typedef struct q_##type {                                                    \
    type *items;                                                               \
    int top;                                                                   \
    int bottom;                                                                \
    int max;                                                                   \
  } q_##type;                                                                  \
                                                                               \
  static q_##type *new_q_##type() {                                            \
                                                                               \
    q_##type *q = (q_##type *)calloc(sizeof(q_##type), 1);                     \
    q->items = (type *)calloc(sizeof(type), QUEUE_MAX);                        \
    q->bottom = 0;                                                             \
    q->top = 1;                                                                \
    q->max = QUEUE_MAX;                                                        \
    return q;                                                                  \
  };                                                                           \
                                                                               \
  static int q_##type##_is_full(q_##type *q) { return q->top == q->max - 1; }  \
                                                                               \
  static int q_##type##_is_empty(q_##type *q) { return q->top == q->bottom; }  \
                                                                               \
  static void q_##type##_push(q_##type *q, type newitem) {                     \
    if (q_##type##_is_full(q)) {                                               \
      q->items = realloc(q->items, q->max + QUEUE_MAX);                        \
      q->max += QUEUE_MAX;                                                     \
    }                                                                          \
    q->items[q->top] = newitem;                                                \
    q->top = (q->top + 1) % q->max;                                            \
  };                                                                           \
                                                                               \
  static type q_##type##_pop_left(q_##type *q) {                               \
    type popped_left = q->items[q->bottom];                                    \
    q->bottom = (q->bottom + 1) % q->max;                                      \
    return popped_left;                                                        \
  };

#endif
