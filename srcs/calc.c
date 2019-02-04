#include "ft_ls.h"

short int	names_len(char **d_names, short int start, short int end)
{
	short int	sum;

	sum = 0;
	while (**d_names == '.')
		*d_names++;
	while (start < end)
		sum += ft_strlen(d_names[start++]) + 3;
	return (sum);
}

short int	count_names(char **d_names)
{
	short int	j;

	j = 0;
	while (**d_names == '.')
    	*d_names++;
	while (d_names[j])
		j++;
	return (j);
}

short int   longest_word(char  **d_names, short int n_n, short int n_r, short int n_c)
{
    short int   j;
    short int   i;
    short int   len;
    short int   k;

    j = -1;
    len = 0;
    k = 0;
    i = -1;
    while (++i < n_c)
        k += n_r;
    while (++j < n_r)
    {
        if (k >= n_n)
            break;
        if (ft_strlen(d_names[k]) > len)
            len = ft_strlen(d_names[k]);
        k++;
    }
    return (len);
}

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