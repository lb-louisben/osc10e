#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct {
    struct timeval timestamp;
} Shared_Data;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>...\n", argv[0]);
        exit(1);
    }

    pid_t pid;
    struct timeval end;

    int size = sizeof(Shared_Data);
    Shared_Data *shared_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid = fork();
    if (pid < 0){
        perror("Fail to fork...\n");
        exit(1);
    } else if (pid == 0) {
        // 子进程：执行传入的命令
        gettimeofday(&shared_data->timestamp, NULL);
        printf("Child: Wrote timestamp (%ld sec, %ld usec)\n",
            shared_data->timestamp.tv_sec,
            shared_data->timestamp.tv_usec);
        execvp(argv[1], &argv[1]);
        perror("execvp"); // 如果 execvp 失败才会执行到这里
    } else {
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&end, NULL);

        // 读取共享内存中的时间
        printf("Parent: Read timestamp (%ld sec, %ld usec)\n",
            shared_data->timestamp.tv_sec,
            shared_data->timestamp.tv_usec);
        long second = end.tv_sec - shared_data->timestamp.tv_sec;
        long microseconds = end.tv_usec - shared_data->timestamp.tv_usec;

        // 释放共享内存
        munmap(shared_data, size);
        printf("Total time elapses %ld sec %ld usec while excute command %s.\n", second, microseconds, argv[1]);
    }

    return 0;
}