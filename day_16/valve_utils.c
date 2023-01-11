#include "../common/list.h"
#include "./const.h"
#include <stdio.h>
#include <string.h>
LIST_TYPE(int)

void print_bits_16(uint16_t bits) {
  int b[16] = {0};
  int i;
  for (i = 0; bits > 0; i++) {
    b[i] = (int)(bits % 2);
    bits = bits / 2;
  }

  for (i = 0; i < 16; i++) {
    printf("%d", b[i]);
  };
  printf("\n");
}

typedef struct node {
  int flow_rate;
  int idx;
  t_list_int *tunnels;
} node;

#ifdef TEST
static const uint16_t TEST_ALL_OPEN = (uint16_t)-1 >> 6;
typedef struct state {
  int total_flow;
  int valve;
  int minute;
  uint16_t open_valves;
} state;
#else
static const uint64_t TEST_ALL_OPEN = (uint16_t)-1 >> 1;
typedef struct state {
  int total_flow;
  int valve;
  int minute;
  uint64_t open_valves;
} state;
#endif

#define QUEUE_MAX 64
typedef struct queue {
  state *items;
  int top;
  int bottom;
  int max;
} queue;
queue *new_queue() {

  queue *q = (queue *)calloc(sizeof(queue), 1);
  q->items = (state *)calloc(sizeof(state), QUEUE_MAX);
  q->bottom = 0;
  q->top = 1;
  q->max = QUEUE_MAX;
  return q;
};

int queue_is_full(queue *q) { return q->top == q->bottom - 1; }

int queue_is_empty(queue *q) { return q->top == q->bottom; }

void resize_queue(queue *q) {
  int new_capacity = q->max + QUEUE_MAX;
  q->items = realloc(q->items, new_capacity);
  q->max = new_capacity;
  if (q->bottom > q->top) {
    for (int i = 0; i < q->bottom; i++) {
      q->items[i + q->max] = q->items[i];
    }
    q->top = q->top + q->max;
  }
  q->top = q->max + q->bottom + 1;
  q->max += QUEUE_MAX;
}
void queue_push(queue *q, state newitem) {
  if (queue_is_full(q)) {
    resize_queue(q);
  }
  q->items[q->top] = newitem;
  q->top = (q->top + 1) % q->max;
};

state queue_pop_left(queue *q) {
  state popped_left = q->items[q->bottom];
  q->bottom = (q->bottom + 1) % q->max;
  return popped_left;
};

node new_node(int flow_rate, int idx) {
  return (node){.flow_rate = flow_rate, .idx = idx, .tunnels = new_list_int()};
}

void add_tunnel(node *node, int tunnel_idx) {
  list_int_append(node->tunnels, tunnel_idx);
}

int valve_is_open(node valve, state valve_state) {
  return (valve_state.open_valves >> valve.idx) & 1;
}

int open_valve(node valve, state *state) {
  int already_open = valve_is_open(valve, *state);
  state->open_valves |= 1 << valve.idx;
  return !already_open;
}

static char *print_base_26(int val) {
  char *chars = malloc(sizeof(char) * 3);
  chars[0] = val / 26 + 'A';
  chars[1] = val % 26 + 'A';
  return chars;
}

int project_total_flow(state state, node valve) {
  int flow_rate = valve.flow_rate;
  return state.total_flow + (TOTAL_TIME - state.minute) * flow_rate;
}

void debug_state(state state) {
  char *name = print_base_26(state.valve);
  printf("v# %s, flow: %d, time: %d, open: ", name, state.total_flow,
         state.minute);
  print_bits_16(state.open_valves);
}

void debug_valves(node valves[ALPHA_CHARS], int valve_indices[NUM_VALVES]) {

  for (int i = 0; i < NUM_VALVES; i++) {
    node v = valves[valve_indices[i]];
    printf("valve #%d flow_rate: %d", i, v.flow_rate);
    int l = v.tunnels->length;

    printf(" tunnels: ");

    for (int j = 0; j < l; j++) {
      printf("t %d ", list_int_at(v.tunnels, j));
    }

    printf("\n");
  }
}

void bfs_valves(int valve_indices[NUM_VALVES],
                node valves[ALPHA_CHARS * ALPHA_CHARS]) {

  queue *queue = new_queue();

  state state = {0, 0, 0, 0};
  queue_push(queue, state);

  while (queue_is_empty(queue) && state.open_valves != TEST_ALL_OPEN) {
    state = queue_pop_left(queue);

    debug_state(state);

    node valve = valves[state.valve];
    int flow_rate = valve.flow_rate;

    int opening = open_valve(valve, &state);

    for (int t = 0; t < valve.tunnels->length; t++) {
      int tunnel = list_int_at(valve.tunnels, t);
      node next_valve = valves[tunnel];
      if (!valve_is_open(next_valve, state) && opening) {

        struct state next_state = {
            .total_flow = project_total_flow(state, next_valve),
            .valve = tunnel,
            .minute = state.minute + 1,
            .open_valves = state.open_valves,
        };

        queue_push(queue, next_state);
      }
    }
  }
  debug_state(state);
}
