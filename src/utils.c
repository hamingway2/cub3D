#include "cub3d.h"

//ft_strlen, ft_strncmp, ft_calloc, ft_strdup, ft_strjoin, ft_substr, ft_strchr

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_line_length(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while(line[i] != '\0' && line[i] != '\n')
		i++;
	return(i);
}