#include "./queue.h"
// Stack implementation in C
//
void stack_new(t_queue_int *s) { s->top = -1; };

void queue_new(t_queue_int *q) {
  q->top = -1;
  q->bottom = -1;
};

int queue_is_full(t_queue_int *q) {
  if (q->top == QUEUE_MAX - 1) {
    return 1;
  }
  return 0;
};
int queue_is_empty(t_queue_int *q) {
  if (q->top == q->bottom) {
    return 1;
  }
  return 0;
};
void queue_push(t_queue_int *q, int newitem) {
  if (queue_is_full(q)) {
    return;
  }
  q->top++;
  q->items[q->top] = newitem;
};
char queue_pop_left(t_queue_int *q) {
  int popped_left = q->items[q->bottom];
  q->bottom++;
  return popped_left;
};
