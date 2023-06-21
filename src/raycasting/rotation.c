#include "../../includes/cub3D.h"

static void	ft_3d_position(t_rc *data, char type)
{
	if (type == 'L')
	{
		data->p3d.old_px = data->p3d.px;
		data->p3d.px = data->p3d.px * cos(ROT_SPEED_LEFT)
			- data->p3d.py * sin(ROT_SPEED_LEFT);
		data->p3d.py = data->p3d.old_px * sin(ROT_SPEED_LEFT)
			+ data->p3d.py * cos(ROT_SPEED_LEFT);
	}
	else if (type == 'R')
	{
		data->p3d.old_px = data->p3d.px;
		data->p3d.px = data->p3d.px * cos(ROT_SPEED_RIGHT)
			- data->p3d.py * sin(ROT_SPEED_RIGHT);
		data->p3d.py = data->p3d.old_px * sin(ROT_SPEED_RIGHT)
			+ data->p3d.py * cos(ROT_SPEED_RIGHT);
	}
}

static void	ft_3d_rotation(t_rc *data, char type)
{
	if (type == 'L')
	{
		data->p3d.old_dx = data->p3d.dir_x;
		data->p3d.dir_x = data->p3d.dir_x * cos(ROT_SPEED_LEFT)
			- data->p3d.dir_y * sin(ROT_SPEED_LEFT);
		data->p3d.dir_y = data->p3d.old_dx * sin(ROT_SPEED_LEFT)
			+ data->p3d.dir_y * cos(ROT_SPEED_LEFT);
		ft_3d_position(data, 'L');
	}
	else if (type == 'R')
	{
		data->p3d.old_dx = data->p3d.dir_x;
		data->p3d.dir_x = data->p3d.dir_x * cos(ROT_SPEED_RIGHT)
			- data->p3d.dir_y * sin(ROT_SPEED_RIGHT);
		data->p3d.dir_y = data->p3d.old_dx * sin(ROT_SPEED_RIGHT)
			+ data->p3d.dir_y * cos(ROT_SPEED_RIGHT);
		ft_3d_position(data, 'R');
	}
}

void	ft_rotation(mlx_key_data_t keydata, t_rc *data)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha += ROT_SPEED_LEFT;
		if (data->player.alpha < 0)
			data->player.alpha += 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
		ft_3d_rotation(data, 'L');
	}
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha += ROT_SPEED_RIGHT;
		if (data->player.alpha > 2 * PI)
			data->player.alpha -= 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
		ft_3d_rotation(data, 'R');
	}
}
