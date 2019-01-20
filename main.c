#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR *dir;

	if (argc == 1)
		check_open(dir = opendir("."));
	else
		check_open(dir = opendir(argv[1]));
	closedir(dir);
	return (0);
}
