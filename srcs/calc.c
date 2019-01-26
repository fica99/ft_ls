#include "ft_ls.h"

short int	names_len(char **d_names, short int j)
{
	short int	i;
	short int	sum;

	i = 0;
	sum = 0;
	while (d_names[i][0] == '.')
		i++;
	while (i < j)
		sum += ft_strlen(d_names[i++]) + 2;
	return (sum);
}

short int	count_names(char **d_names)
{
	short int	j;
	short int	d;

	j = 0;
	d = 0;
	while (d_names[d][0] == '.')
		d++;
	j = d;
	while (d_names[j])
		j++;
	return (j - d);
}

short int   longest_word(char  **d_names, short int n_r, short int n_c)
{
    short int   i;
    short int   j;
    short int   len;
    short int   k;

    i = 0;
    while (d_names[i][0] == '.')
        i++;
    j = 0;
    len = 0;
    k = 0;
    while (k < n_c)
        k += n_r;
    while (j < n_r)
    {
        if (ft_strlen(d_names[k + i]) > len)
            len = ft_strlen(d_names[k + i]);
        j++;
        k++;
    }
    return (len);
}