#include <stdio.h>
#include <stdlib.h>

void printError(int error)
{
	switch(error)
	{
		case 0:
			printf("Unable to allocate memory!\n");
			break;
	}
	return;
}
