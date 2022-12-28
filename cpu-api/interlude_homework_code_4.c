#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        
        int rc = fork();

        if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0) {
                // child process
                printf("Child: Hello! pid %d\n", (int) getpid());
                char *args[2];
                args[0] = "/bin/ls";
                args[1] = NULL;
                execv(args[0], args);
        } else {
                // parent process

                // seems that it's necessary to wait() to let child process run
                // first
                wait(NULL);
                printf("Parent: Goodbye! pid %d\n", (int) getpid());
        }
        return 0;
}
