#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct option option;

void process_input(int argc, char **argv, option *long_options);
void handle_flags(char flag, FILE *f);
void process_default_mode(int argc, char **argv, int flag_used);
int open_file(char *filename, FILE **file_ptr);
void flag_n(FILE *f);
void flag_b(FILE *f);
void flag_e(FILE *f, int use_v);
void flag_s(FILE *f);
void flag_t(FILE *f, int use_v);
char flag_v(char ch);
void print_file(FILE *f);

int main(int argc, char **argv) {
  option long_options[] = {{"number", no_argument, NULL, 'n'},
                           {"number-nonblank", no_argument, NULL, 'b'},
                           {"squeeze-blank", no_argument, NULL, 's'},
                           {0, 0, 0, 0}};
  process_input(argc, argv, long_options);
  return 0;
}

void process_input(int argc, char **argv, option *long_options) {
  int opt, flag_used = 0;

  while ((opt = getopt_long(argc, argv, "beEnsvtT", long_options, 0)) != -1) {
    for (int i = optind; i < argc; i++) {
      FILE *file = NULL;
      if (open_file(argv[i], &file)) {
        handle_flags(opt, file);
        fclose(file);
        flag_used = 1;
      }
    }
  }
  if (flag_used == 0) {
    process_default_mode(argc, argv, flag_used);
  }
}

void handle_flags(char flag, FILE *f) {
  if (flag == 'b') flag_b(f);
  if (flag == 'e') flag_e(f, 1);
  if (flag == 'E') flag_e(f, 0);
  if (flag == 'n') flag_n(f);
  if (flag == 's') flag_s(f);
  if (flag == 't') flag_t(f, 1);
  if (flag == 'T') flag_t(f, 0);
}

void process_default_mode(int argc, char **argv, int flag_used) {
  if (optind < argc && flag_used == 0) {
    for (int i = optind; i < argc; i++) {
      FILE *file = NULL;
      if (open_file(argv[i], &file)) {
        print_file(file);
        fclose(file);
      }
    }
  }
}

int open_file(char *filename, FILE **file_ptr) {
  int success = 0;
  *file_ptr = fopen(filename, "r");
  if (*file_ptr != NULL) {
    success = 1;
  } else {
    perror(filename);
  }
  return success;
}

void flag_n(FILE *f) {
  int c, line_number = 1, is_new_line = 1;

  while ((c = fgetc(f)) != EOF) {
    if (is_new_line) {
      printf("%6d\t", line_number++);
      is_new_line = 0;
    }
    putchar(c);
    if (c == '\n') is_new_line = 1;
  }
}

void flag_b(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_number = 1;

  while ((read = getline(&line, &len, f)) != -1) {
    if (line[0] != '\n') {
      printf("%6d\t%s", line_number++, line);
    } else {
      printf("%s", line);
    }
  }
  free(line);
}

void flag_e(FILE *f, int use_v) {
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      printf("$\n");
    } else {
      putchar(use_v ? flag_v(c) : c);
    }
  }
}

void flag_s(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int prev_empty = 0;

  while ((read = getline(&line, &len, f)) != -1) {
    if (line[0] == '\n') {
      if (prev_empty == 0) {
        printf("%s", line);
      }
      prev_empty = 1;
    } else {
      printf("%s", line);
      prev_empty = 0;
    }
  }
  free(line);
}

void flag_t(FILE *f, int use_v) {
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\t') {
      printf("^I");
    } else {
      putchar(use_v ? flag_v(c) : c);
    }
  }
}

char flag_v(char ch) {
  unsigned char uch = (unsigned char)ch;

  if (uch > 127 && uch < 160) {
    printf("M-^");
    uch -= 128;
  }
  if ((uch < 32 && uch != '\n' && uch != '\t') || uch == 127) {
    printf("^");
    uch = (uch == 127) ? '?' : uch + 64;
  }
  return (char)uch;
}

void print_file(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    putchar(c);
  }
}