#include "../../includes/cub3D.h"

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
		rows++;
		idx++;
	}
	return (rows);
}

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

int	map_builder(t_init *init, int idx)
{
	while (check_empty_line(init->in_cnt[idx]))
		idx++;
	if (!check_first_line(init->in_cnt[idx]))
		return (0);
	init->map->height = get_map_rows(init, idx);
	init->map->map = malloc(sizeof(char *) * init->map->height + 1);
	if (!init->map->map)
		ft_puterr_fd("Error\nNot enough memory available", 2, 1);
	map_normalizer(init, idx);
	map_checker(init);
	return (1);
}
