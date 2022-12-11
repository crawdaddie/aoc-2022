#include "../common/str_utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WAIT_TIME 10
#define ROWS 512
#define COLS 512

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

void render(Knot r[10], int pos[ROWS][COLS]) {

  printf("\033[2J");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      char render_char = '.';
      for (int ri = 0; ri < 10; ri++) {
        render_char = is_at(r[ri], j, ROWS - 1 - i) ? ri + '0' : render_char;
      }
      render_char = pos[ROWS - 1 - i][j] ? '#' : render_char;
      printf("%c", render_char);
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

void write_ppm(int pos[ROWS][COLS]) {
  const char *filename = "./output.pgm";
  int x, y;
  /* size of the image */
  /* 2D array for colors (shades of gray) */
  /* color component is coded from 0 to 255 ;  it is 8 bit color file */
  unsigned char data[ROWS][COLS];
  const int MaxColorComponentValue = 255;
  FILE *fp;
  /* comment should start with # */
  const char *comment = "# this is my new binary pgm file";

  /* fill the data array */
  for (y = 0; y < ROWS; ++y) {
    for (x = 0; x < COLS; ++x) {
      data[y][x] = 255 - (pos[y][x] ? 255 : 0);
    }
  }

  /* write the whole data array to ppm file in one step */
  /* create new file, give it a name and open it in binary mode */
  fp = fopen(filename, "wb");
  /* write header to the file */
  fprintf(fp, "P5\n %s\n %d\n %d\n %d\n", comment, COLS, ROWS,
          MaxColorComponentValue);
  /* write image data bytes to the file */
  fwrite(data, sizeof(data), 1, fp);
  fclose(fp);
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

  Knot r[10];

  for (int ri = 0; ri < 10; ri++) {
    r[ri].x = COLS / 2;
    r[ri].y = ROWS / 2;
  }

  int pos[ROWS][COLS] = {0};

  while ((read = getline(&line, &line_len, file)) != -1) {
    int steps;
    char d;
    parse_move(line, &d, &steps);
    for (int s = 0; s < steps; s++) {
      move_head(&r[0], d, 1);
      for (int ki = 1; ki < 10; ki++) {
        move_tail(r + ki, *(r + ki - 1));
      }

      Knot t = r[9];

      if (!pos[t.y][t.x]) {
        pos[t.y][t.x] = 1;
        *score += 1;
      }
    }

    /* render(r, pos); */
    /* for (int ri = 0; ri < 10; ri++) { */
    /*   printf("%d %d %d\n", ri, r[ri].x, r[ri].y); */
    /* } */

    i++;
  }

  fclose(file);
  write_ppm(pos);
}

int main(int argc, char **argv) {
  int score = 0;
  process_lines("./input.txt", &score);
  printf("your score part2: %d\n", score);
  return 0;
}
