#include "filesize.h"

int main()
{
	char buffer[100];
	int file = open("file.txt", O_RDONLY);
	int count = 0;
    int n_read;

	do
	{
		n_read = read(file, buffer, 10);
		count += n_read;
		printf("%d\n", n_read);
	} while (n_read != 0);

	printf("Read returns %d bytes\n", count);


	count = 0;

	lseek(file, 0, SEEK_SET);
	count = lseek(file, 0, SEEK_END);

	printf("lseek returns %d bytes\n", count);

	close(file);

	return 0;
}