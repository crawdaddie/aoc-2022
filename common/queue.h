#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 64
typedef struct t_queue_int {
  int items[QUEUE_MAX];
  int top;
  int bottom;
} t_queue_int;

void queue_new(t_queue_int *q);
int queue_is_full(t_queue_int *q);
int queue_is_empty(t_queue_int *q);
void queue_push(t_queue_int *q, int newitem);
char queue_pop_left(t_queue_int *q);

#endif
