#include "ft_ls.h"

void		change_names(char **d_names, short int i)
{
	char	*arr;

	arr = d_names[i];
	d_names[i] = d_names[i + 1];
	d_names[i + 1] = arr;
}

char		**sort_names(char **d_names)
{
	short int	i;
	short int	j;

	i = 0;
	j = double_arr_len(d_names);
	while (i < j - 1)
	{
		if (ft_strcmp(d_names[i], d_names[i + 1]) > 0)
		{
			change_names(d_names, i);
			i = -1;
		}
		i++;
	}
	return (d_names);
}

short int	double_arr_len(char **d_names)
{
	short int	i;

	i = 0;
	while (d_names[i])
		i++;
	return (i);
}