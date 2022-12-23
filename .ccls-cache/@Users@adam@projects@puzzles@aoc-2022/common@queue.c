#include "./queue.h"

q_int *q_new(int *items, size_t num_items, int max) {

  q_int *q = (q_int *)calloc(sizeof(q_int), 1);
  q->items = (int *)calloc(sizeof(int), max);
  for (int i = 0; i < num_items; i++) {
    q->items[i] = items[i];
  }
  q->bottom = 0;
  q->top = num_items;
  q->max = max;
  return q;
};
int q_is_full(q_int *q) {
  if (q->top == q->max - 1) {
    return 1;
  }
  return 0;
};
int q_is_empty(q_int *q) {
  if (q->top == q->bottom) {
    return 1;
  }
  return 0;
};
void q_push(q_int *q, int newitem) {
  if (q_is_full(q)) {
    return;
  }
  q->items[q->top] = newitem;
  q->top = (q->top + 1) % q->max;
};

int q_left(q_int *q) {
  int popped_left = q->items[q->bottom];
  q->bottom = (q->bottom + 1) % q->max;
  return popped_left;
};
