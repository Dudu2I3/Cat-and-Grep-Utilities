#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
  int error_flag;
} arguments;

void print_line(char* line, int line_length);
void process_file(FILE* file, char* filename, regex_t* regex, arguments arg);
void append_pattern(arguments* arg, char* pattern);
int load_patterns_from_file(arguments* arg, char* file_path);
void print_matching_part(regex_t* regex, char* line);
void handle_arguments_and_process_files(int argc, char** argv, regex_t* regex,
                                        arguments* arg);

int main(int argc, char** argv) {
  regex_t regex;
  arguments arg = {0};
  arg.error_flag = 0;
  handle_arguments_and_process_files(argc, argv, &regex, &arg);
  regfree(&regex);
  return arg.error_flag;
}

void handle_arguments_and_process_files(int argc, char** argv, regex_t* regex,
                                        arguments* arg) {
  int opt;
  int status = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg->e = 1;
        append_pattern(arg, optarg);
        break;
      case 'i':
        arg->i = REG_ICASE;
        break;
      case 'v':
        arg->v = 1;
        break;
      case 'c':
        arg->c = 1;
        break;
      case 'l':
        arg->l = 1;
        break;
      case 'n':
        arg->n = 1;
        break;
      case 'h':
        arg->h = 1;
        break;
      case 's':
        arg->s = 1;
        break;
      case 'f':
        arg->f = 1;
        if (load_patterns_from_file(arg, optarg) != 0) {
          arg->error_flag = 1;
          status = 1;
        }
        break;
      case 'o':
        arg->o = 1;
        break;
    }
  }
  if (status == 0 && arg->len_pattern == 0 && optind < argc) {
    append_pattern(arg, argv[optind++]);
  }
  if (status == 0 && arg->len_pattern != 0) {
    int error = regcomp(regex, arg->pattern, REG_EXTENDED | arg->i);
    if (error) {
      perror("Error compiling regex");
      arg->error_flag = 1;
      status = 1;
    }
  }
  if (status == 0 && argc - optind == 1) {
    arg->h = 1;
  }
  for (int i = optind; i < argc && status == 0; i++) {
    FILE* file = fopen(argv[i], "r");
    if (file != NULL) {
      process_file(file, argv[i], regex, *arg);
    } else if (!arg->s) {
      perror(argv[i]);
      arg->error_flag = 1;
      status = 1;
    }
  }
}

void print_line(char* line, int line_length) {
  for (int i = 0; i < line_length; i++) {
    putchar(line[i]);
  }
  if (line[line_length - 1] != '\n') {
    putchar('\n');
  }
}

int load_patterns_from_file(arguments* arg, char* file_path) {
  FILE* file = fopen(file_path, "r");
  int status = 0;
  if (file == NULL) {
    if (!arg->s) perror(file_path);
    status = 1;
  } else {
    char* line = NULL;
    size_t length = 0;
    int read = getline(&line, &length, file);
    while (read != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      append_pattern(arg, line);
      read = getline(&line, &length, file);
    }
    free(line);
    fclose(file);
  }
  return status;
}

void process_file(FILE* file, char* filename, regex_t* regex, arguments arg) {
  char* line = NULL;
  size_t length = 0;
  int line_number = 1;
  int match_count = 0;
  int status = 0;

  while (status == 0 && getline(&line, &length, file) != -1) {
    int result = regexec(regex, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", filename);
        if (arg.n) printf("%d:", line_number);
        if (arg.o)
          print_matching_part(regex, line);
        else
          print_line(line, strlen(line));
      }
      match_count++;
    }
    line_number++;
  }

  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  if (arg.l && match_count > 0) {
    printf("%s\n", filename);
  }

  free(line);
  fclose(file);
}

void append_pattern(arguments* arg, char* pattern) {
  if (arg->len_pattern > 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void print_matching_part(regex_t* regex, char* line) {
  regmatch_t match;
  int offset = 0;
  int status = 0;

  while (status == 0) {
    int result = regexec(regex, line + offset, 1, &match, 0);
    if (result != 0) {
      status = 1;
    } else {
      for (int i = match.rm_so; i < match.rm_eo; i++) {
        putchar(line[i]);
      }
      putchar('\n');
      offset += match.rm_eo;
    }
  }
}