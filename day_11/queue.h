
typedef struct q_int {
  int *items;
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
