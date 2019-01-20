#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void    check_open(DIR *dir);
void    check_close(int nb);
char    **arr_names(DIR *dir);
#endif
