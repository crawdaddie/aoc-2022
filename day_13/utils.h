#ifndef _DAY_13_UTILS
#define _DAY_13_UTILS
#include <stdio.h>

/* typedef union PacketWrapper { */
/*   int64_t integer;     // Integer value */
/*   struct Packet *list; // Nested packet */
/* } PacketWrapper; */

typedef struct list_int {
  int *items;
  int length;
  int max;
} t_list;

typedef struct list_str {
  char **items;
  int length;
  int max;
} t_list_str;

typedef struct list_list {
  t_list *list;
  int length;
  int max;
} t_list_list;

void incr(char **packet);

int compare_lines(t_list_str *l_stack, t_list_str *r_stack);

t_list_str *new_list_str(char *init_val);
void list_append(t_list_str *l, char *item);
char *list_pop(t_list_str *l);
int list_is_empty(t_list_str *l);
char *list_last(t_list_str *l);

#endif
