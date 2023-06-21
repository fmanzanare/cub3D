#include "../../includes/cub3D.h"

void	ft_print_direction(t_rc *data)
{
	int	t;
	int	x;
	int	dx;
	int	y;
	int	dy;

	t = -1;
	dx = 2 + t * (data->player.dx / MULT_DELTA);
	dy = 2 + t * (data->player.dy / MULT_DELTA);
	x = MAP_WIDTH / 2 + dx;
	y = MAP_HEIGHT / 2 + dy;
	memset(data->img_h->pixels, 0, MAP_WIDTH * MAP_HEIGHT * 4);
	while (t++ < MAP_WIDTH
		&& !is_wall(data, data->player.y + dy, data->player.x + dx))
	{
		dx = 2 + t * (data->player.dx / MULT_DELTA);
		dy = 2 + t * (data->player.dy / MULT_DELTA);
		x = MAP_WIDTH / 2 + dx;
		y = MAP_HEIGHT / 2 + dy;
		if (x < MAP_WIDTH && x > 0 && y < MAP_HEIGHT && y > 0)
			mlx_put_pixel(data->img_h, x, y, 0xFF00FFFF);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;

	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_3d_displacement(data, 'W');
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_3d_displacement(data, 'S');
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_3d_displacement(data, 'A');
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_3d_displacement(data, 'D');
	ft_rotation(keydata, data);
	raycast(data);
	ft_print_direction(data);
	ft_print_minimap(data);
}
