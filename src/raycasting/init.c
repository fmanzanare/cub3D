#include "../../includes/cub3D.h"

static void	ft_print_player(t_rc *data)
{
	int	*pointer;
	int	p;

	p = 0;
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
}

static void	ft_orientation(t_rc *data, char type)
{
	if (type == 'E')
	{
		data->player.alpha = PI;
		data->p3d.px = 0;
		data->p3d.py = -0.66;
	}
	else if (type == 'N')
	{
		data->player.alpha = (3 * PI) / 2;
		data->p3d.px = 0.66;
		data->p3d.py = 0;
	}
	else if (type == 'W')
	{
		data->player.alpha = 0;
		data->p3d.px = 0;
		data->p3d.py = 0.66;
	}
	else if (type == 'S')
	{
		data->player.alpha = PI / 2;
		data->p3d.px = -0.66;
		data->p3d.py = 0;
	}
}

void	ft_player_finder(t_rc *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map->height)
	{
		while (x < data->map->width)
		{
			if (data->map->map[y][x] > 'A' && data->map->map[y][x] < 'Z')
			{
				data->player.x = (x * PIX_SQ) + (PIX_SQ / 2) + 0.5;
				data->player.y = (y * PIX_SQ) + (PIX_SQ / 2) + 0.5;
				ft_orientation(data, data->map->map[y][x]);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_init(t_rc *data, t_init *init)
{
	data->map = init->map;
	data->img_p = mlx_new_image(data->mlx, 8, 8);
	ft_memset(data->img_p->pixels, 255,
		data->img_p->width * data->img_p->height * 4);
	data->img_h = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	ft_player_finder(data);
	data->player.dx = cos(data->player.alpha);
	data->player.dy = sin(data->player.alpha);
	data->p3d.dir_x = data->player.dx;
	data->p3d.dir_y = data->player.dy;
	data->player.dx *= MULT_DELTA;
	data->player.dy *= MULT_DELTA;
	data->p3d.pos_x = (data->player.x / PIX_SQ);
	data->p3d.pos_y = (data->player.y / PIX_SQ);
	ft_print_player(data);
	data->img_map = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	ft_memset(data->img_map->pixels, 255,
		data->img_map->width * data->img_map->height * 4);
	ft_print_minimap(data);
}
