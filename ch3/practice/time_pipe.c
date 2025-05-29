#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define BUFFER_SIZE 32
#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {
    pid_t pid;
    static struct timeval start, end, pipe_read;
    int fd[2];

    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fail to fork...\n");
        exit(1);
    }

    if (pid == 0) {
        close(fd[READ_END]);
        gettimeofday(&start, NULL);
        write(fd[WRITE_END], &start, sizeof(struct timeval));
        close(fd[WRITE_END]);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&end, NULL);
        close(fd[WRITE_END]);
        read(fd[READ_END], &pipe_read, sizeof(struct timeval));
        close(fd[READ_END]);
        long second = end.tv_sec - pipe_read.tv_sec;
        long microseconds = end.tv_usec - pipe_read.tv_usec;
        printf("Total time elapses %ld sec %ld usec while excute command %s.\n", second, microseconds, argv[1]);
    }
    return 0;
}