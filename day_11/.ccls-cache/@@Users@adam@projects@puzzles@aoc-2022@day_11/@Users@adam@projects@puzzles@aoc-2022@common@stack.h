#ifndef _STACK
#define _STACK
#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 64

typedef struct t_stack {
  char items[STACK_MAX];
  int top;
} t_stack;

void stack_new(t_stack *s);
int stack_is_full(t_stack *s);
int stack_is_empty(t_stack *s);
void stack_push(t_stack *s, char newitem);
char stack_pop(t_stack *s);

typedef struct t_queue_int {
  int items[STACK_MAX];
  int top;
  int bottom;
} t_queue_int;

void queue_new(t_queue_int *q);
int queue_is_full(t_queue_int *q);
int queue_is_empty(t_queue_int *q);
void queue_push(t_queue_int *q, int newitem);
char queue_pop_left(t_queue_int *q);

#endif
