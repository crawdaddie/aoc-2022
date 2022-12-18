#include "./utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void incr(char **packet) {
  if (**packet != '\n') {
    *packet += 1;
  }
}
#define MAX 64

t_list_str *new_list_str(char *init_val) {
  char **items = calloc(sizeof(char *), MAX);
  *items = init_val;

  t_list_str *list = calloc(sizeof(t_list_str), 1);
  list->items = items;

  list->length = init_val == NULL ? 0 : 1;
  list->max = MAX;
  return list;
}

void list_append(t_list_str *l, char *item) {
  l->items[l->length] = item;
  l->length += 1;
}
char *list_pop(t_list_str *l) {
  char *item = l->items[l->length - 1];
  l->length -= 1;
  return item;
}
int list_is_empty(t_list_str *l) { return l->length == 0; }
char *list_last(t_list_str *l) { return l->items[l->length - 1]; }

int is_digit(char *str) { return !(*str == ']' || *str == ']' || *str == ','); }

int is_list_start(char *str) { return *str == '['; }
int starts_with_comma(char *str) { return *str == ','; }

int list_start(char *str) { return *str == '['; }

int list_end(char *str) { return *str == ']'; }

int comma(char *str) { return *str == ','; }

void handle_list_start(char *str) {}
void increment_head(t_list_str *l) { l->items[l->length]++; }

int int_val(char *str) {
  int v;
  if (sscanf("%d", str, &v) == 0) {
    return -1;
  } else {
    return v;
  };
}

int compare_lines(t_list_str *l, t_list_str *r) {
  while (!list_is_empty(l) && !list_is_empty(r)) {
    char *left = list_last(l);
    char *right = list_last(r);
    if (is_digit(left) && is_digit(right)) {
      if (int_val(left) > int_val(right)) {
        return 0;
      }
    }
    if (!list_start(left) && list_start(right)) {
      list_append(l, left++);
      list_append(r, right++);
      continue;
    }
  }
}
