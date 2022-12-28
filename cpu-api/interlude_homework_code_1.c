#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        
        int x = 100;
        int *x_ptr = &x;
        int rc = fork();

        if (rc == 0) {
                // child process
                printf("Child: pid %d\n", (int) getpid());
                printf("x: %d\n", x);
                *x_ptr = 200;
        } else {
                // parent process
                wait(NULL);
                printf("Parent: pid %d\n", (int) getpid());
                printf("x: %d\n", x);
        }
        return 0;
}
