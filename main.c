#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	if (!access(av[1], F_OK))
		printf("salut\n");
	else
		printf("no dir\n");
}

