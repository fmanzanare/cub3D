#include "../../includes/cub3D.h"

static int	ft_set_pixel_color(t_rc *data, int x, int y)
{
	int	max_width;
	int	max_heigth;
	int	y_map;
	int	x_map;

	y_map = y / PIX_SQ;
	x_map = x / PIX_SQ;
	max_width = data->map->width;
	max_heigth = data->map->height;
	if ((x_map < max_width && x_map >= 0)
		&& (y_map >= 0 && y_map < max_heigth))
	{
		return (data->map->map[y_map][x_map] == '1'
		|| data->map->map[y_map][x_map] == '.'
		|| data->map->map[y_map][x_map] == '\0');
	}
	else
		return (1);
}

void	ft_print_minimap(t_rc *data)
{
	double	y;
	double	y_aux;
	double	x;
	double	x_aux;

	y = data->player.y - MAP_HEIGHT / 2;
	x = data->player.x - MAP_WIDTH / 2;
	y_aux = y;
	x_aux = x;
	while (y - y_aux < MAP_HEIGHT)
	{
		while (x - x_aux < MAP_WIDTH)
		{
			if (ft_set_pixel_color(data, x, y))
				mlx_put_pixel(data->img_map, x - x_aux, y - y_aux, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->img_map, x - x_aux, y - y_aux, 0x000000FF);
			x++;
		}
		x = x_aux;
		y++;
	}
}
