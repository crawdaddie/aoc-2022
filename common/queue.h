#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 64
typedef struct q_int {
  int items[QUEUE_MAX];
  int top;
  int bottom;
} q_int;

void queue_new(q_int *q);
int queue_is_full(q_int *q);
int queue_is_empty(q_int *q);
void queue_push(q_int *q, int newitem);
char queue_pop_left(q_int *q);

#define QUEUE_TYPE(type)                                                       \
  typedef struct t_q_##type {                                                  \
    type *items;                                                               \
    int top;                                                                   \
    int bottom;                                                                \
    int max;                                                                   \
  } t_q_##type;                                                                \
                                                                               \
  t_q_##type *q_##type##_new(type *items, size_t num_items, int max) {         \
                                                                               \
    t_q_##type *q = (t_q_##type *)calloc(sizeof(t_q_pos), 1);                  \
    q->items = (type *)calloc(sizeof(type), max);                              \
    for (int i = 0; i < num_items; i++) {                                      \
      q->items[i] = items[i];                                                  \
    }                                                                          \
    q->bottom = 0;                                                             \
    q->top = num_items;                                                        \
    q->max = max;                                                              \
    return q;                                                                  \
  };                                                                           \
  int q_##type##_is_full(t_q_##type *q) {                                      \
    if (q->top == q->max - 1) {                                                \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  };                                                                           \
  int q_##type##_is_empty(t_q_##type *q) {                                     \
    if (q->top == q->bottom) {                                                 \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  };                                                                           \
  void q_##type##_push(t_q_##type *q, type newitem) {                          \
    if (q_##type##_is_full(q)) {                                               \
      return;                                                                  \
    }                                                                          \
    q->items[q->top] = newitem;                                                \
    q->top = (q->top + 1) % q->max;                                            \
  };                                                                           \
                                                                               \
  type q_##type##_pop_left(t_q_##type *q) {                                    \
    type popped_left = q->items[q->bottom];                                    \
    q->bottom = (q->bottom + 1) % q->max;                                      \
    return popped_left;                                                        \
  };

#endif
