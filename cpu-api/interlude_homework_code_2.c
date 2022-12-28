#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        
        FILE *fp;
        fp = fopen("interlude_homework_code_2_output.txt", "a+");

        int rc = fork();

        if (rc == 0) {
                // child process
                fprintf(fp, "Child: pid %d\n", (int) getpid());
        } else {
                // parent process
                wait(NULL);
                fprintf(fp, "Parent: pid %d\n", (int) getpid());
        }

        fclose(fp);
        return 0;
}
