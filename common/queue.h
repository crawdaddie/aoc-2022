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

#endif
