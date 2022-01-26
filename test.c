#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int	fd;
	int	ret;
	char	buffer[1000];

	fd = open("pics/barrel.png", O_RDONLY);
	printf("this is the return value of open %d\n", fd);
	memset(buffer, 0, 1000);
	ret = read(fd, buffer, 999);
	printf("%s\n", buffer);
	while (ret > 0)
	{
		memset(buffer, 0, 1000);
		ret = read(fd, buffer, 999);
	}
	return (0);	
}

