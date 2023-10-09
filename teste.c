#include <unistd.h>

int main(void)
{
	char *command = "/usr/bin/ls";

	char *arguments[] = {command, "-l", "-a", NULL };

	execve(command, arguments, NULL);

	execve(struct.command, struct.path, NULL);
}

