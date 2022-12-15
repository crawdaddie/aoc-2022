#define WITH_INPUT(input_file, callback, ...) \
  FILE *file = fopen(input_file, "r"); \
  size_t read; \
  char *line = NULL; \
  size_t line_len = 0; \
  int i = 0; \
  while ((read = getline(&line, &line_len, file)) != -1) { \
    callback(line, i, __VA_ARGS__); \
    i++; \
  } \
  fclose(file); \


