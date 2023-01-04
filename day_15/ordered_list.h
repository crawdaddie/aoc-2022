#include <stdio.h>
#include <stdlib.h>

#define LL_TYPE(type)                                                          \
  typedef struct ll_##type {                                                   \
    type item;                                                                 \
    struct ll_##type *next;                                                    \
  } ll_##type;                                                                 \
                                                                               \
  ll_##type *node(type item) {                                                 \
                                                                               \
    ll_##type *new_element = malloc(sizeof(ll_##type));                        \
    new_element->item = item;                                                  \
    new_element->next = NULL;                                                  \
    return new_element;                                                        \
  }                                                                            \
                                                                               \
  void insert_before(ll_##type *l, type item) {                                \
    type old_item = l->item;                                                   \
    ll_##type *old_next = l->next;                                             \
    l->item = item;                                                            \
    l->next = node(old_item);                                                  \
    l->next->next = old_next;                                                  \
  }                                                                            \
                                                                               \
  void insert_after(ll_##type *l, type item) {                                 \
    if (l == NULL) {                                                           \
      *l = (ll_##type *)malloc(sizeof(ll_##type));                             \
      l->next = NULL;                                                          \
      l->item = item;                                                          \
      return;                                                                  \
    }                                                                          \
                                                                               \
    ll_##type *next = l->next;                                                 \
                                                                               \
    ll_##type *new_element = malloc(sizeof(ll_##type));                        \
    new_element->item = item;                                                  \
    new_element->next = next;                                                  \
                                                                               \
    l->next = new_element;                                                     \
  }
