#include "../../includes/cub3D.h"

char	*get_tex_or_color(char *str)
{
	char	*ret;
	int		i;

	str += 2;
	i = 0;
	while (ft_isspecialchar(*str))
		str++;
	ret = malloc(sizeof(char) * (ft_strlen(str)));
	while (*str && *str != '\n')
	{
		ret[i] = *str;
		i++;
		str++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	check_cardinal(t_init *init, char *str)
{
	if (*str == 'N' && str[1] == 'O')
	{
		init->map->n_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'S' && str[1] == 'O')
	{
		init->map->s_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'W' && str[1] == 'E')
	{
		init->map->w_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'E' && str[1] == 'A')
	{
		init->map->e_tex = get_tex_or_color(str);
		return (1);
	}
	return (0);
}

int	check_texture(t_init *init, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != '\n')
	{
		while (ft_isspecialchar(*tmp))
			tmp++;
		if (check_cardinal(init, tmp))
			return (1);
		tmp++;
	}
	return (0);
}
