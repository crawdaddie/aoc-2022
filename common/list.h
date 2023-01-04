#include <assert.h>
#define LIST_MAX 64
#define LIST_TYPE(type)                                                        \
  typedef struct list_##type {                                                 \
    type *items;                                                               \
    int length;                                                                \
    int max;                                                                   \
  } t_list_##type;                                                             \
                                                                               \
  t_list_##type *new_list_##type() {                                           \
    type *items = calloc(sizeof(type), LIST_MAX);                              \
    t_list_##type *list = calloc(sizeof(t_list_##type), 1);                    \
    list->items = items;                                                       \
    list->length = 0;                                                          \
    list->max = LIST_MAX;                                                      \
    return list;                                                               \
  }                                                                            \
                                                                               \
  void list_##type##_append(t_list_##type *l, type item) {                     \
    if (l->length == l->max - 1) {                                             \
      l->items = realloc(l->items, l->max + LIST_MAX);                         \
      l->max += LIST_MAX;                                                      \
    }                                                                          \
    l->items[l->length] = item;                                                \
    l->length += 1;                                                            \
  }                                                                            \
                                                                               \
  int list_##type##_is_empty(t_list_##type *l) { return l->length == 0; }      \
                                                                               \
  type list_##type##_pop(t_list_##type *l) {                                   \
    assert(!list_##type##_is_empty(l));                                        \
    type item = l->items[l->length - 1];                                       \
    l->length -= 1;                                                            \
    return item;                                                               \
  }                                                                            \
                                                                               \
  type list_##type##_at(t_list_##type *l, int i) {                             \
    assert(!list_##type##_is_empty(l));                                        \
    assert(i < l->length);                                                     \
    type item = l->items[i];                                                   \
    return item;                                                               \
  }\
