#include "../common/input.h"
#include "../common/list.h"
#include "../common/str_utils.h"
#include "./ordered_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define LINE_NUM 10 */
#define LINE_NUM 2000000

typedef struct interval {
  int start;
  int end;
} interval;

typedef struct node {
  interval item;
  struct node *next;
} node;

node *new_node(interval item) {
  node *n = (node *)malloc(sizeof(node));
  n->item = item;
  n->next = NULL;
  return n;
}
int intervals_intersect(interval rng_a, interval rng_b) {
  /* printf("find intersection between (%d %d) and (%d %d)", rng_a.start, */
  /*        rng_a.end, rng_b.start, rng_b.end); */
  if (rng_a.start <= rng_b.end && rng_a.end >= rng_b.start) {
    /* printf("- true\n"); */
    return 1;
  }
  /* printf("- false\n"); */
  return 0;
}

void insert_after(node *n, interval item) {
  node *old_next = n->next;
  node *next = new_node(item);
  next->next = old_next;
  n->next = next;
}

void remove_after(node *n) {
  node *next = n->next;
  n->next = next->next;
  free(next);
}

void insert_before(node *n, interval item) {
  insert_after(n, n->item);
  n->item = item;
}

void debug_ll(node *n) {
  node *cur = n;
  while (cur) {
    int start = cur->item.start;
    int end = cur->item.end;
    printf("(%d %d)\n", start, end);

    cur = cur->next;
  }
}

int max(int int_a, int int_b) { return int_a > int_b ? int_a : int_b; }
int min(int int_a, int int_b) { return int_a < int_b ? int_a : int_b; }

void resolve_intervals(node *head, interval it) {
  interval item = head->item;

  if (intervals_intersect(it, item)) {
    head->item.start = min(it.start, item.start);
    head->item.end = max(it.end, item.end);
    node *next = head->next;
    while (next && intervals_intersect(head->item, next->item)) {
      interval head_item = head->item;
      interval next_item = next->item;
      node *next_next = next->next;
      remove_after(head);
      head->item.start = min(head_item.start, next_item.start);
      head->item.end = max(head_item.end, next_item.end);
      next = next_next;
    }

    return;
  }

  if (it.start < item.start && it.end < item.start) {
    insert_before(head, it);
    return;
  }

  if (it.start > item.end && head->next) {
    return resolve_intervals(head->next, it);
  }
  return insert_after(head, it);
}

void project_onto_line(int line_num, int manhattan_radius, int x, int y,
                       node *head) {
  int vert_distance = abs(line_num - y);
  int projection_len = 2 * (manhattan_radius - vert_distance);

  if (projection_len > 0) {
    interval it = {.start = x - projection_len / 2,
                   .end = x + projection_len / 2};

    if (head->item.start == 0 && head->item.end == 0 && head->next == NULL) {
      head->item = it;
    } else {
      resolve_intervals(head, it);
    }
  }
}

LIST_TYPE(int);
void process_line(char *line, int i, node *lhead) {
  int x, y, bx, by, manhattan_radius;

  parsef("Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", line, &x, &y,
         &bx, &by);

  manhattan_radius = abs(x - bx) + abs(y - by);

  project_onto_line(LINE_NUM, manhattan_radius, x, y, lhead);
}

int main(int argc, char **argv) {

  interval null_int = {0, 0};
  node *lnode = new_node(null_int);

  WITH_INPUT_LINES("./input.txt", process_line, lnode);

  node *cur = lnode;
  int line_beacon = 1765036;

  int count = 0;
  printf("collected:\n");
  while (cur) {
    int start = cur->item.start;
    int end = cur->item.end;
    printf("(%d %d)\n", start, end);
    count += end + 1 - start;

    if (start <= line_beacon && line_beacon <= end) {
      count -= 1;
    }

    cur = cur->next;
  }

  printf("%d positions cannot contain a beacon on line %d\n", count, LINE_NUM);

  return 0;
}
