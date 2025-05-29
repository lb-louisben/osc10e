/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 /* 80 chars per line, per command */

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	char input[MAX_LINE];
    int should_run = 1;
	int background = 0;
		
    while (should_run){   
        printf("osh>");
        fflush(stdout);

		if(fgets(input, sizeof(MAX_LINE), stdin) == NULL) {
			break;
		}

		// 去除换行符
		input[strcspn(input, "\n")] = '\0';

		int argc = 0;
		char *token = strtok(input, " ");

		while (token != NULL && argc < MAX_LINE/2) {
            // 检查是否为后台运行符 &
            if (strcmp(token, "&") == 0) {
                background = 1;
                break;
            }
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL; // execvp 要求参数以 NULL 结尾

		// 打印解析结果
        printf("[解析结果]\n");
        printf("命令: %s\n", args[0]);
        printf("参数: ");
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n后台运行: %s\n", background ? "是" : "否");

        // 重置状态
        background = 0;
        
        /**
         * After reading user input, the steps are:
         * (1) fork a child process
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         */
    }
    
	return 0;
}
