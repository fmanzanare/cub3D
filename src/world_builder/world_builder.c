#include "../../includes/cub3D.h"

static void	print_c_and_f(t_rc *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < (HEIGHT / 2))
				mlx_put_pixel(data->img_bg, x, y, data->map->c_hex);
			else
				mlx_put_pixel(data->img_bg, x, y, data->map->f_hex);
			x++;
		}
		y++;
	}
}

void	world_builder(t_rc *data)
{
	data->img_bg = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ft_memset(data->img_bg->pixels, 255, data->img_bg->width
		* data->img_bg->height * 4);
	print_c_and_f(data);
	data->img_world = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}
