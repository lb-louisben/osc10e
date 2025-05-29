/**
 * Figure 3.31
 total 8 process
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	fork();

	fork();

	fork();
	
	return 0;
}
