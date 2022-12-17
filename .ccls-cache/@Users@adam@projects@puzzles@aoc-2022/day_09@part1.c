#include "../common/str_utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WAIT_TIME 200
#define ROWS 1000
#define COLS 1000

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec) {
  struct timespec ts;
  int res;

  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}

typedef struct Knot {
  int x;
  int y;
} Knot;

int is_at(Knot k, int x, int y) { return k.x == x && k.y == y; };

void render(Knot h, Knot t, int pos[ROWS][COLS]) {

  printf("\033[2J");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int pos_h = is_at(h, j, ROWS - 1 - i);
      int pos_t = is_at(t, j, ROWS - 1 - i);

      if (pos_h && pos_t) {
        printf("H");
        continue;
      }

      if (pos_h) {
        printf("H");
        continue;
      }

      if (pos_t) {
        printf("T");
        continue;
      }

      printf(pos[ROWS - 1 - i][j] ? "#" : ".");
    }
    printf("\n");
  }

  msleep(WAIT_TIME);
}

void move_head(Knot *h, char d, int steps) {
  switch (d) {
  case 'U': {
    h->y += steps;
  } break;

  case 'D': {
    h->y -= steps;
  } break;

  case 'L': {
    h->x -= steps;
  } break;

  case 'R': {
    h->x += steps;
  } break;
  }
}
void move_tail(Knot *t, Knot h) {
  int diffx = h.x - t->x;
  int diffy = h.y - t->y;
  if (diffx * diffx <= 1 && diffy * diffy <= 1) {
    return;
  }

  if (diffx != 0 && diffy != 0) {
    t->x += diffx > 0 ? 1 : -1;
    t->y += diffy > 0 ? 1 : -1;
    return;
  }

  if (diffy == 0) {
    t->x += diffx > 0 ? 1 : -1;
    return;
  }

  if (diffx == 0) {
    t->y += diffy > 0 ? 1 : -1;
    return;
  }
}

void parse_move(char *line, char *d, int *steps) {
  *steps = atoi(line + 2);
  *d = line[0];
}

void process_lines(char *input_file, int *score) {
  FILE *file = fopen(input_file, "r");
  size_t read;
  char *line = NULL;
  size_t line_len = 0;
  int i = 0;
  /* Knot r[10]; */
  /* for (int ri = 0; ri < 10; ri++) { */
  /*   r[ri].x = COLS / 2; */
  /*   r[ri].y = ROWS / 2; */
  /* } */
  Knot h = {COLS / 2, ROWS / 2};
  Knot t = {COLS / 2, ROWS / 2};

  int pos[ROWS][COLS] = {0};

  while ((read = getline(&line, &line_len, file)) != -1) {
    int steps;
    char d;
    parse_move(line, &d, &steps);
    for (int s = 0; s < steps; s++) {
      move_head(&h, d, 1);
      /* render(h, t, pos); */
      move_tail(&t, h);
      printf("h %d %d | t %d %d\n", h.x, h.y, t.x, t.y);

      if (!pos[t.y][t.x]) {
        pos[t.y][t.x] = 1;
        *score += 1;
      }
      /* render(h, t, pos); */
    }

    i++;
  }

  fclose(file);
}

int main(int argc, char **argv) {
  int score = 0;
  process_lines("./input.txt", &score);
  printf("your score part1: %d\n", score);
  return 0;
}
