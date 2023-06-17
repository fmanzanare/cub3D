#include "../../includes/cub3D.h"

static void	ft_rotation(mlx_key_data_t keydata, t_rc *data)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha -= ALPHA_INC;
		if (data->player.alpha < 0)
			data->player.alpha += 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
	}
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha += ALPHA_INC;
		if (data->player.alpha > 2 * PI)
			data->player.alpha -= 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
	}
}

static void	ft_is_wall(t_rc *data, double py, double px, char type)
{
	int	yp;
	int	xp;
	char **map = data->map->map;

	yp = (int)py / (MAP_HEIGHT / data->map->height);
	xp = (int)px / (MAP_WIDTH / data->map->width);
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'W')
		data->player.x += data->player.dx;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'W')
		data->player.y += data->player.dy;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'S')
		data->player.x -= data->player.dx;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'S')
		data->player.y -= data->player.dy;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'A')
		data->player.x += data->player.dy;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'A')
		data->player.y -= data->player.dx;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'D')
		data->player.x -= data->player.dy;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'D')
		data->player.y += data->player.dx;
	data->img_p->instances[0].y = data->player.y;
	data->img_p->instances[0].x = data->player.x;
}

static int	is_wall(t_rc *data, double py, double px)
{
	int	x;
	int	y;

	x = (int)px /(MAP_WIDTH / data->map->width);
	y = (int)py /(MAP_HEIGHT / data->map->height);
	return data->map->map[y][x] == '1';
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;
	int		t;

	t = -1;
	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y + data->player.dy,data->player.x + data->player.dx, 'W');
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y - data->player.dy,data->player.x - data->player.dx, 'S');
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y - data->player.dx, data->player.x + data->player.dy, 'A');
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y + data->player.dx, data->player.x - data->player.dy, 'D');
	ft_rotation(keydata, data);
	// cabeza del jugador
	memset(data->img_h->pixels, 0,data->img_h->width * data->img_h->height * 4 );
	while (t++ < MAP_WIDTH && !is_wall(data, data->player.y + 2 + t * (data->player.dy/MULT_DELTA), data->player.x + 2 + t * (data->player.dx/MULT_DELTA)))
		mlx_put_pixel(data->img_h, data->player.x + 2 + t * (data->player.dx/MULT_DELTA), (data->player.y + 2) + t * (data->player.dy/MULT_DELTA), 0xFF00FFFF);
}