#include "../../includes/cub3D.h"

static int	get_max_row(t_init *init, int idx)
{
	int	len;
	int	aux;
	int	i;

	i = idx;
	aux = 0;
	len = 0;
	while (init->in_cnt[i])
	{
		aux = ft_strlen(init->in_cnt[i]);
		if (aux > len)
			len = aux;
		i++;
	}
	return (len);
}

void	normalizer_loop(t_init *init, int idx)
{
	while (init->col < (init->map->width - 1))
	{
		if (!init->in_cnt[idx][init->aux_idx])
		{
			init->map->map[init->row][init->col] = '.';
			init->col++;
			continue ;
		}
		else if (ft_isspecialchar(init->in_cnt[idx][init->aux_idx]))
			init->map->map[init->row][init->col] = '.';
		else
			init->map->map[init->row][init->col]
				= init->in_cnt[idx][init->aux_idx];
		init->col++;
		init->aux_idx = init->col;
	}
}

void	map_normalizer(t_init *init, int idx)
{
	init->aux_idx = 0;
	init->col = 0;
	init->row = 0;
	init->map->width = get_max_row(init, idx);
	while (init->in_cnt[idx])
	{
		init->col = 0;
		init->aux_idx = 0;
		init->map->map[init->row] = malloc(sizeof(char)
				* (init->map->width + 1));
		normalizer_loop(init, idx);
		init->map->map[init->row][init->col] = '\0';
		idx++;
		init->row++;
	}
	init->map->map[init->row] = NULL;
}
