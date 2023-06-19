#include "../../includes/cub3D.h"

void	ft_set_minimap_color(t_rc *data, int x, int y, int *color)
{
	if (x < data->map->width * PIX_SQ && y < data->map->height * PIX_SQ)
		*color = data->map->map[y / PIX_SQ][x / PIX_SQ] == '1';
	else
		*color = 1;
}

void	ft_print_minimap(t_rc *data)
{
	int	y;
	int	y_aux;
	int	x;
	int	x_aux;
	int	color;

	color = 0;
	y = data->player.y + (PIX_SQ / 2);
	x = data->player.x + (PIX_SQ / 2);
	y_aux = y;
	x_aux = x;
	while(y - y_aux < MAP_HEIGHT)
	{
		while (x - x_aux < MAP_WIDTH)
		{
			// printf("x %d\n", x / data->sq_size_x);
			ft_set_minimap_color(data, x, y, &color);
			if (color)
				mlx_put_pixel(data->img_map, x - x_aux, y - y_aux, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->img_map, x - x_aux, y - y_aux, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}
}
