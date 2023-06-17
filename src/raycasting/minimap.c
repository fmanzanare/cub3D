#include "../../includes/cub3D.h"

void	ft_set_minimap_color(t_rc *data, int x, int y, int *color)
{
	int	fy;
	int fx;

	fy = (y / data->sq_size_y) + data->player.arr_y;
	fx = (x / data->sq_size_x) + data->player.arr_x;
	if (fx < data->map->width && fy < data->map->height)
		*color = data->map->map[fy][fx] == '1';
	else
		*color = 1;
}

void	ft_print_minimap(t_rc *data)
{
	int	y;
	int	x;
	int	color;

	color = 0;
	y = 0;
	x = 0;
	data->sq_size_x = MAP_WIDTH / TOT_SQ;
	data->sq_size_y = MAP_HEIGHT / TOT_SQ;
	while(y < MAP_HEIGHT && (y / data->sq_size_y) < data->map->height)
	{
		while (x < MAP_WIDTH && (x / data->sq_size_x) < data->map->width)
		{
			ft_set_minimap_color(data, x, y, &color);
			if (color)
				mlx_put_pixel(data->img_map, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->img_map, x, y, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}
}
