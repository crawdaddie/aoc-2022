#include <stdio.h>
#include <string.h>

int main() {
  char string[] = "2-4,6-8";
  char *token;

  token = strtok(string, "-,");

  if (token == NULL) {
    puts("empty string");
    return 1;
  }

  while (token) {
    puts(token);
    token = strtok(NULL, "-,");
  }

  return 0;
}
