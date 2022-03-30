/*
 * heavy.c: spawns a logging intensive workload,
 * characterized by writes to disk simultaneously
 */
#define _GNU_SOURCE
#include "random.h"
#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define KILOBYTE 1024

pthread_mutex_t locks[25];
pthread_mutex_t start_timer;
int started = 0;
struct timeval write_start;

struct __attribute__((__packed__)) ThreadData {
  int write_size;
  char file_number;
  int write_number;
};

void output_usage_and_end(int exit_code) {
  printf("USAGE:   ./heavy [-r repetitions] [-s write_size]\n\n");
  printf("OPTIONS: -r: number of total writes performed\n");
  printf("         -s: size of writes, in KB\n");
  printf("NOTES:   repetitions and write_size must be greater than 0\n");
  exit(exit_code);
}

void *perform_write(void *thread_data) {
  pthread_mutex_lock(&start_timer);
  if (!started) {
    gettimeofday(&write_start, NULL);
    started = 1;
  }
  pthread_mutex_unlock(&start_timer);

  struct ThreadData *td = thread_data;
  char filename[7];
  char *buf = generate_random_data(td->write_size, 33, 126);

  strncpy(filename, "/tmp/", 6);
  filename[5] = td->file_number;
  filename[6] = '\0';

  pthread_mutex_lock(&locks[td->file_number - 'A']);
  int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IWGRP);
  int bytes = write(fd, buf, td->write_size);
  close(fd);
  pthread_mutex_unlock(&locks[td->file_number - 'A']);
  // printf("Write %d of size %d to %s\n", td->write_number, bytes, filename);
  free(buf);
  free(td);
  return NULL;
}

int main(int argc, char const *argv[]) {
  int repetitions = 200;
  int write_size = 64 * KILOBYTE;
  struct timeval write_end;
  int seconds;
  int microseconds;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strstr(argv[i], "-h") != NULL) {
        output_usage_and_end(EXIT_SUCCESS);
      } else if (strstr(argv[i], "-r") != NULL) {
        if (i + 1 >= argc) {
          output_usage_and_end(EXIT_FAILURE);
        }
        repetitions = atoi(argv[i + 1]);
        if (repetitions == 0) {
          printf("Reptitions must be greater than 0\n");
          output_usage_and_end(EXIT_FAILURE);
        }
      } else if (strstr(argv[i], "-s") != NULL) {
        if (i + 1 >= argc) {
          output_usage_and_end(EXIT_FAILURE);
        }
        write_size = atoi(argv[i + 1]) * KILOBYTE;
        if (write_size == 0) {
          printf("Write size must be greater than 0\n");
          output_usage_and_end(EXIT_FAILURE);
        }
      }
    }
  }

  printf("Reps: %d, Write Size: %d\n", repetitions, write_size);

  pthread_t threads[repetitions];

  for (int i = 0; i < 25; i++) {
    pthread_mutex_init(&locks[i], NULL);
  }
  pthread_mutex_init(&start_timer, NULL);

  for (int i = 0; i < repetitions; i++) {
    struct ThreadData *td = malloc(sizeof(struct ThreadData));
    assert(td != NULL);
    td->write_size = write_size;
    td->file_number = (i % 25) + 'A';
    td->write_number = i;

    pthread_create(&threads[i], NULL, perform_write, (void *)td);
  }
  for (int i = 0; i < repetitions; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&write_end, NULL);
  seconds = write_end.tv_sec - write_start.tv_sec;
  microseconds = write_end.tv_usec - write_start.tv_usec;
  printf("Time elapsed: %ds %dus\n", seconds, microseconds);
  float bandwidth =
      (repetitions * write_size) / ((seconds * 1000000) + microseconds);
  bandwidth *= 1000;
  printf("Bandwidth: %0.0f bytes/sec\n", bandwidth);

  exit(EXIT_SUCCESS);
}
