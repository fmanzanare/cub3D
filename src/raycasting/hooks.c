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

static int	ft_check_index(t_rc *data, int y, int x)
{
	if (y > data->map->height || y < 0)
		return (1);
	if (x > data->map->width || x < 0)
		return (1);
	return (0);
}

static int	is_wall(t_rc *data, double py, double px)
{
	int	x;
	int	y;

	x = (int)px / PIX_SQ;
	y = (int)py / PIX_SQ;
	if (ft_check_index(data, y, x))
		return (1);
	return data->map->map[y][x] == '1';
}

static void	ft_is_wall(t_rc *data, double py, double px, char type)
{
	int	sum_y;
	int	sum_x;
	int	y_index;
	int	x_index;
	char **map = data->map->map;

	y_index = (int)data->player.y / PIX_SQ; 
	x_index = (int)data->player.x / PIX_SQ;
	sum_y = (int)py / PIX_SQ;
	sum_x = (int)px / PIX_SQ;
	if (ft_check_index(data, y_index, x_index))
		return ;
	else if (ft_check_index(data, sum_y, sum_x))
		return ;
	if (map[y_index][sum_x] != '1' && type == 'W')
		data->player.x += data->player.dx;
	if (map[sum_y][x_index] != '1' && type == 'W')
		data->player.y += data->player.dy;
	if (map[y_index][sum_x] != '1' && type == 'S')
		data->player.x -= data->player.dx;
	if (map[sum_y][x_index] != '1' && type == 'S')
		data->player.y -= data->player.dy;
	if (map[y_index][sum_x] != '1' && type == 'A')
		data->player.x += data->player.dy;
	if (map[sum_y][x_index] != '1' && type == 'A')
		data->player.y -= data->player.dx;
	if (map[y_index][sum_x] != '1' && type == 'D')
		data->player.x -= data->player.dy;
	if (map[sum_y][x_index] != '1' && type == 'D')
		data->player.y += data->player.dx;
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
	{
			if (MAP_WIDTH / 2 + 2 + t * (data->player.dx/MULT_DELTA) < MAP_WIDTH && MAP_WIDTH / 2 + 2 + t * (data->player.dx/MULT_DELTA) < MAP_WIDTH > 0
				&& MAP_HEIGHT / 2 + 2 + t * (data->player.dy/MULT_DELTA) < MAP_HEIGHT && MAP_HEIGHT / 2 + 2 + t * (data->player.dy/MULT_DELTA) > 0)
				mlx_put_pixel(data->img_h, MAP_WIDTH / 2 + 2 + t * (data->player.dx/MULT_DELTA), MAP_HEIGHT / 2 + 2 + t * (data->player.dy/MULT_DELTA), 0xFF00FFFF);
	}
	ft_print_minimap(data);
}