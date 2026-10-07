# include "cub3d.h"

int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (FALSE);
	return (ft_strncmp(filename + len - ft_strlen(EXTENSION),
			EXTENSION, ft_strlen(EXTENSION) + 1) == 0);
}

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
		return (error_msg(USAGE_INFO));
	if (has_cub_extension(av[1]) == FALSE)
		return (error_msg(WRONG_EXTENSION));
	return (TRUE);
}
