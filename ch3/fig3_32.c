/**
 * Figure 3.32
 * 2^4 = 16 processes...
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int i;

	for (i = 0; i < 4; i++)
		fork();
	
	return 0;
}
