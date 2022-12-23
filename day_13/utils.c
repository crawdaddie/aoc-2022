#include "./utils.h"
#include "../common/str_utils.h"
#include <math.h>
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
  /* printf("appended: `%s`\n", item); */
  l->items[l->length] = item;
  l->length += 1;
}
int list_is_empty(t_list_str *l) {
  /* printf("list is empty check %d, %s\n", l->length, l->items[0]); */
  return l->length == 0;
}
char *list_pop(t_list_str *l) {
  if (list_is_empty(l)) {
    return NULL;
  }
  char *item = l->items[l->length - 1];
  l->items[l->length - 1] = NULL;
  l->length -= 1;
  return item;
}

int list_start(char *str) { return *str == '['; }
int list_end(char *str) { return *str == ']'; }
int comma(char *str) { return *str == ','; }
int digit(char *str) { return !(*str == ']' || *str == ']' || *str == ','); }

int int_val(char *str) {
  int v;
  if (sscanf("%d", str, &v) == 0) {
    return -1;
  } else {
    return v;
  };
}
void print_stack(t_list_str *st0, t_list_str *st1) {
  int max = (st0->length > st1->length ? st0->length : st1->length);
  for (int i = 0; i < max; i++) {
    printf("%d: `%s \t\t %s`\n", i, st0->items[i], st1->items[i]);
  }
  printf("-------\n");
}

int compare_lines(t_list_str *l, t_list_str *r) {
  while (!list_is_empty(l) || !list_is_empty(r)) {

    char *left = list_pop(l);
    char *right = list_pop(r);

    if (comma(left)) {
      left++;
    }
    if (comma(right)) {
      right++;
    }

    print_stack(l, r);

    if (digit(left) && digit(right)) {
      int left_val, right_val;
      parse_int_n(&left, ",]", 2, &left_val);
      parse_int_n(&right, ",]", 2, &right_val);

      if (left_val > right_val) {
        return 0;
      }

      list_append(l, left + 1);
      list_append(r, right + 1);
    }

    if (list_start(left) && list_start(right)) {
      list_append(l, left + 1);
      list_append(r, right + 1);
      continue;
    }

    if (list_start(left) && digit(right)) {
      list_append(l, left + 1);
      list_append(r, right);
      continue;
    }

    if (list_end(left) && list_end(right)) {
      l->items[l->length - 1] = left + 1;
      r->items[r->length - 1] = right + 1;
      continue;
    }
  }
  return 1;
}
