#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sched.h>

void printf_time(char* str) {
        struct timeval* timestamp = malloc(sizeof(struct timeval));
        gettimeofday(timestamp, NULL);

        printf("%d secs %d microsecs | %s", (int) timestamp->tv_sec, (int) timestamp->tv_usec, str);
        free(timestamp);
}

/*
 * Measurements
 */
int main(int argc, char* argv[]) {
        int pipe1[2];
        int pipe2[2];
        int c = 10;
        int cpu = 0;
        cpu_set_t set;

        CPU_SET(cpu, &set);

        pipe(pipe1);
        pipe(pipe2);

        int child = fork();
        sched_setaffinity(getpid(), sizeof(set), &set);

        if (child < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (child == 0) {
                // process 1

                char* msg = "from process 1";
                char* buf = malloc(strlen(msg));
                char* read_result = malloc(100);

                while (c) {
                        
                        memset(buf, 0, strlen(buf));
                        memset(read_result, 0, strlen(read_result));

                        printf_time("process 1 begins\n");
                        // write to pipe1
                        printf_time("process 1 writes to pipe1\n");
                        write(pipe1[1], msg, strlen(msg));

                        // read from pipe2
                        printf_time("process 1 trying to read from pipe2\n");
                        read(pipe2[0], buf, strlen(msg));

                        sprintf(read_result, "process 1 read from pipe2: %s\n", buf);
                        printf_time(read_result);

                        printf_time("process 1 ends\n");
                        c--;
                }
                free(buf);
                free(read_result);
                
        } else {
                // process 2
                        
                char* msg = "from process 2";
                char* buf = malloc(strlen(msg));
                char* read_result = malloc(100);

                while (c) {
                        memset(buf, 0, strlen(buf));
                        memset(read_result, 0, strlen(read_result));

                        printf_time("process 2 begins\n");

                        // read from pipe1
                        printf_time("process 2 trying to read from pipe1\n");
                        read(pipe1[0], buf, strlen(msg));

                        sprintf(read_result, "process 2 read from pipe1: %s\n", buf);
                        printf_time(read_result);

                        // write to pipe2
                        printf_time("process 2 writes to pipe2\n");
                        write(pipe2[1], msg, strlen(msg));

                        printf_time("process 2 ends\n");
                        c--;
                }

                free(buf);
                free(read_result);
        }
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        return 0;
}
