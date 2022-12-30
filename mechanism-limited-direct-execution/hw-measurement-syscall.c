#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/*
 * Measurements
 */
int main(int argc, char* argv[]) {
        char* buf = malloc(1);
        int counts = 10000;
        int fd = open("./file.txt", O_RDONLY);
        int diff;

        struct timeval* start = malloc(sizeof(struct timeval));
        struct timeval* end = malloc(sizeof(struct timeval));

        gettimeofday(start, NULL);
        for (int i = 0; i < counts; i++)
                read(fd, buf, 0);
        gettimeofday(end, NULL);

        diff = (end->tv_sec * 1000000 + end->tv_usec) - (start->tv_sec * 1000000 + start->tv_usec);

        printf("per read() time: %.4f microseconds\n", (float) diff / counts);

        free(buf);
        free(start);
        free(end);
        close(fd);
        return 0;
}
