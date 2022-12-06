#include "./stack.h"
// Stack implementation in C
//
void stack_new(t_stack *s) { s->top = -1; };

// Check if the stack is full
int stack_is_full(t_stack *s) {
  if (s->top == STACK_MAX - 1)
    return 1;
  else
    return 0;
}

// Check if the stack is empty
int stack_is_empty(t_stack *s) {
  if (s->top == -1)
    return 1;
  else
    return 0;
}

// Add elements into stack
void stack_push(t_stack *s, char newitem) {
  if (stack_is_full(s)) {
    return;
    /* printf("STACK FULL"); */
  };
  s->top++;
  s->items[s->top] = newitem;
}

// Remove element from stack
char stack_pop(t_stack *s) {
  if (stack_is_empty(s)) {
    return '\0';
  };
  char popped = s->items[s->top];
  s->top--;
  return popped;
}
