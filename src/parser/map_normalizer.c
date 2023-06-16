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

void	map_normalizer(t_init *init, int idx)
{
	int		col;
	int		row;
	int		aux_idx;

	aux_idx = 0;
	col = 0;
	row = 0;
	init->map->width = get_max_row(init, idx);
	while (init->in_cnt[idx])
	{
		col = 0;
		aux_idx = 0;
		init->map->map[row] = malloc(sizeof(char) * (init->map->width + 1));
		while (col < (init->map->width - 1))
		{
			if (!init->in_cnt[idx][aux_idx])
			{
				init->map->map[row][col] = '.';
				col++;
				continue ;
			}
			else if (ft_isspecialchar(init->in_cnt[idx][aux_idx]))
				init->map->map[row][col] = '.';
			else
				init->map->map[row][col] = init->in_cnt[idx][aux_idx];
			col++;
			aux_idx = col;
		}
		init->map->map[row][col] = '\0';
		idx++;
		row++;
	}
	init->map->map[row] = NULL;
}
