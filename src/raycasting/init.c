#include "../../includes/cub3D.h"

static void	ft_print_player(t_rc *data)
{
	int	*pointer;
	int	p;
	p = 0; // iterador
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
}

static void	ft_orientation(t_rc *data, char type)
{
	if (type == 'E')
		data->player.alpha = PI;
	else if (type == 'N')
		data->player.alpha = (3 * PI) / 2;
	else if (type == 'W')
		data->player.alpha = 0;
	else if (type == 'S')
		data->player.alpha = PI / 2;
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
				data->player.x = (x * PIX_SQ) + (PIX_SQ / 2);
				data->player.y = (y * PIX_SQ) + (PIX_SQ / 2);
				// printf("origin y: %f, x: %f\n", data->player.y, data->player.x);
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
	// printf("map height: %d, map width: %d\n", data->map->height, data->map->width);
	// init de player
	data->img_p = mlx_new_image(data->mlx, P_SIZE, P_SIZE);
	memset(data->img_p->pixels, 255, data->img_p->width * data->img_p->height * 4);
	data->img_h = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	ft_player_finder(data);
	data->player.x = MAP_WIDTH / 2;
	data->player.y = MAP_HEIGHT / 2;
	data->player.dx = cos(data->player.alpha) * 5;
	data->player.dy = sin(data->player.alpha) * 5;
	ft_print_player(data);
	// init de map
	data->img_map = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	memset(data->img_map->pixels, 255, data->img_map->width * data->img_map->height * 4);
	data->sq_size_x = MAP_WIDTH / TOT_SQ;
	data->sq_size_y = MAP_HEIGHT / TOT_SQ;
}