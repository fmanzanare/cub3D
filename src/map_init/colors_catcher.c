#include "../../includes/cub3D.h"

static int	check_cf(t_init *init, char *str)
{
	if (*str == 'F')
	{
		init->f_rgb = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'C')
	{
		init->c_rgb = get_tex_or_color(str);
		return (1);
	}
	return (0);
}

int	check_colors(t_init *init, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != '\n')
	{
		while (ft_isspecialchar(*tmp))
			tmp++;
		if (check_cf(init, tmp))
			return (1);
		tmp++;
	}
	return (0);
}
