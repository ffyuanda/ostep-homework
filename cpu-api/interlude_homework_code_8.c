#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
        
        int pipefd[2];
        if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
        }

        int child1 = fork();
        char buf;

        if (child1 < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (child1 == 0) {
                // child1 process (write)
                printf("Child1 start: pid %d\n", (int) getpid());

                char *msg = "from_Child1";
                close(pipefd[0]);
                write(pipefd[1], msg, strlen(msg));
                close(pipefd[1]);

                printf("Child1 end: pid %d\n", (int) getpid());
        } else {
                // parent process
                printf("Parent start: pid %d\n", (int) getpid());

                int child2 = fork();
                
                if (child2 < 0) {
                        fprintf(stderr, "fork failed\n");
                        exit(EXIT_FAILURE);
                } else if (child2 == 0) {
                        // child2 process (read)
                        printf("Child2 start: pid %d\n", (int) getpid());

                        close(pipefd[1]);
                        while (read(pipefd[0], &buf, 1) > 0)
                                write(STDOUT_FILENO, &buf, 1);
                        write(STDOUT_FILENO, "\n", 1);
                        close(pipefd[0]);

                        printf("Child2 end: pid %d\n", (int) getpid());
                } else {
                        close(pipefd[1]);
                        // close(pipefd[0]);
                        int child1_pid = waitpid(child1, NULL, 0);
                        int child2_pid = waitpid(child2, NULL, 0);
                        printf("Waited child1_pid: %d\n", child1_pid);
                        printf("Waited child2_pid: %d\n", child2_pid);

                        printf("Parent end: pid %d\n", (int) getpid());
                }
                
        }
        return 0;
}
