#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
	char **path_list;

	path_list = (char **)malloc(sizeof(char *) * 3);
	path_list[0] = "./hello";
	path_list[1] = "Miguel";
	path_list[2] = NULL;
	execve(path_list[0], path_list, NULL);
}
