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
                int within_child_wait_pid = wait(NULL);
                printf("within_child_wait_pid: %d\n", within_child_wait_pid);
        } else {
                // parent process
                int child_pid = wait(NULL);
                printf("Parent: Goodbye! pid %d\n", (int) getpid());
                printf("Waited child PID: %d\n", child_pid);
        }
        return 0;
}
