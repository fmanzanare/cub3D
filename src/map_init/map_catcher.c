#include "../../includes/cub3D.h"

/* MAP UTILS */
static int check_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspecialchar(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int get_map_rows(t_init *init, int idx)
{
	int	rows;

	rows = 0;
	while (init->in_cnt[idx])
	{
		idx++;
		rows++;
	}
	return (rows);
}

/* MAP CATCHER */
static int	check_first_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && !ft_isspecialchar(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_map(t_init *init, int idx)
{
	int	i;

	while (check_empty_line(init->in_cnt[idx]))
		idx++;
	if (!check_first_line(init->in_cnt[idx]))
		return (0);
	init->map->map = malloc(sizeof(char *) * get_map_rows(init, idx) + 1);
	if (!init->map->map)
		ft_puterr_fd("Error\nNot enough memory available", 2, 1);
	i = 0;
	while (init->in_cnt[idx])
	{
		init->map->map[i] = ft_strdup(init->in_cnt[idx]);
		idx++;
		i++;
	}
	init->map->map[i] = NULL;
	return (1);
}
