#include "../../includes/cub3D.h"

static char *get_tex(char *str)
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
	puts(ret);
	return (ret);
}

static int check_cardinal(t_init *init, char *str)
{
	if (*str == 'N' && str[1] == 'O')
	{
		printf("map %p\n", init->map);
		init->map->n_tex = get_tex(str);
		return (1);
	}
	else if (*str == 'S' && str[1] == 'O')
	{
		init->map->s_tex = get_tex(str);
		return (1);
	}
	else if (*str == 'W' && str[1] == 'E')
	{
		init->map->w_tex = get_tex(str);
		return (1);
	}
	else if (*str == 'E' && str[1] == 'A')
	{
		init->map->e_tex = get_tex(str);
		return (1);
	}
	return (0);
}

static int check_texture(t_init *init, char *str)
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

static void	map_parser(t_init *init)
{
	int	i;

	i = 0;
	while (init->in_cnt[i])
	{
		if (check_texture(init, init->in_cnt[i]))
		{
			i++;
			continue ;
		}
		i++;
	}
}

/* ******************************************** */
// TEMPORAL CHECKER FUNCTION!!!
static void	print_incnt(t_init *init, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s", init->in_cnt[i]);
		i++;
	}

	printf("North tex: %s\n", init->map->n_tex);
	printf("South tex: %s\n", init->map->s_tex);
	printf("West tex: %s\n", init->map->w_tex);
	printf("East tex: %s\n", init->map->e_tex);
}
/* ******************************************** */

void	map_reader(t_init *init)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (read(init->in_fd, &tmp, 1) > 0)
	{
		if (tmp == '\n')
			i++;
	}
	close(init->in_fd);
	init->in_cnt = malloc(sizeof(char *) * (i + 1));
	if (!init->in_cnt)
		ft_puterr_fd("Error\nNot enough memory available", 2, 1);
	init->in_fd = open(init->in_route, O_RDONLY);
	while (j < i)
	{
		init->in_cnt[j] = get_next_line(init->in_fd);
		j++;
	}
	map_parser(init);
	print_incnt(init, i); // TEMPORAL CHECKER FUNCTION!
}
