#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	pid_t pid;
	pid = fork();

	if(pid < 0) {
		perror("Fail to fork...\n");
	} else if (pid == 0) {
	printf("Child (PID=%d): ich liebe dich, GFD...\n", getpid());
		exit(0);
	} else {
		printf("Parent (PID=%d): I am the parent process...\n", getpid());
		sleep(20);
	}
	return 0;
}
