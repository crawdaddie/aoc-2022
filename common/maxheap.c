#include "./maxheap.h"
LIST_TYPE(int);
typedef t_list_int max_heap;

max_heap *new_max_heap() {
  max_heap *heap = new_list_int();
  return heap;
}

void insert(max_heap *h) {}
