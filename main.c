#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*file;
	char			*arr;
	char			*arr1;
	char			**d_names;

	if (argc == 1)
		check_open(dir = opendir("."));
	else
		check_open(dir = opendir(argv[1]));
	while ((file = readdir(dir)) != NULL)
	{
		if (!arr)
        	arr = ft_strnew(1);
        arr1 = ft_strjoin(arr, file->d_name);
        free(arr);
        arr = arr1;
		arr[ft_strlen(arr) + 1] = '\0';
		arr[ft_strlen(arr)] = '.';
		arr1 = NULL;
	}
	d_names = ft_strsplit(arr, '.');
	ft_putstr(d_names[0]);
	check_close(closedir(dir));
	return (0);
}
