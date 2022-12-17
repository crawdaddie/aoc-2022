#ifndef _STACK
#define _STACK
#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 64

typedef struct t_stack {
  char items[STACK_MAX];
  int top;
} t_stack;

// Check if the stack is full
void stack_new(t_stack *s);
int stack_is_full(t_stack *s);
int stack_is_empty(t_stack *s);
void stack_push(t_stack *s, char newitem);
char stack_pop(t_stack *s);

#endif
