#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

//  Usage: ./file_copy source_file_name duplicate_file_name
int main(int argc, char* argv[]) {


	if (argc < 3){
		printf("Usage: ./file_copy ./source_file_name ./duplicate_file_name\n");
		return 1;
	}

	/**
	source file exist or not?
	*/

	int fd1 =  open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		perror("Fail to read the source file, ");
		exit(1);
	}

	int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if (fd2 == -1) {
		perror("Fail to create the duplicated file, ");
		close(fd1);
		exit(1);
	}

	ssize_t bytes_read;
	char buffer[BUFFER_SIZE];

	while ((bytes_read = read(fd1, buffer, BUFFER_SIZE)) > 0) {
		ssize_t bytes_write = write(fd2, buffer, bytes_read);
		if (bytes_read != bytes_write) {
			perror("fail to duplicate a file, ");
			close(fd1);
			close(fd2);
			exit(1);
		}
	}

	close(fd1);
	close(fd2);

	printf("succes to duplicate a file\n");

	return 0;
}
