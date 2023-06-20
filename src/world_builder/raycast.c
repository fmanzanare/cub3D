#include "../../includes/cub3D.h"

static void	print_walls(t_rc *data, int x)
{
	if (data->p3d.side == 0)
		data->p3d.pwd = (data->p3d.sdx - data->p3d.ddx);
	else
		data->p3d.pwd = (data->p3d.sdy - data->p3d.ddy);
	data->p3d.l_height = (int)(HEIGHT / data->p3d.pwd);
	data->p3d.d_start = (data->p3d.l_height * -1) / 2 + HEIGHT / 2;
	if (data->p3d.d_start < 0)
		data->p3d.d_start = 0;
	data->p3d.d_end = data->p3d.l_height / 2 + HEIGHT / 2;
	if (data->p3d.d_end >= HEIGHT)
		data->p3d.d_end = HEIGHT - 1;
	put_textures(data, x);
}

static void	look_for_wall_loop(t_rc *data)
{
	while (data->p3d.hit == 0)
	{
		if (data->p3d.sdx < data->p3d.sdy)
		{
			data->p3d.sdx += data->p3d.ddx;
			data->p3d.map_x += data->p3d.step_x;
			data->p3d.side = 0;
		}
		else
		{
			data->p3d.sdy += data->p3d.ddy;
			data->p3d.map_y += data->p3d.step_y;
			data->p3d.side = 1;
		}
		if (data->map->map[data->p3d.map_y][data->p3d.map_x] == '1')
			data->p3d.hit = 1;
	}
}

static void	get_side_dist(t_rc *data)
{
	if (data->p3d.ray_dx < 0)
	{
		data->p3d.step_x = -1;
		data->p3d.sdx = (data->p3d.pos_x - data->p3d.map_x)
			* data->p3d.ddx;
	}
	else
	{
		data->p3d.step_x = 1;
		data->p3d.sdx = (data->p3d.map_x + 1.0 - data->p3d.pos_x)
			* data->p3d.ddx;
	}
	if (data->p3d.ray_dy < 0)
	{
		data->p3d.step_y = -1;
		data->p3d.sdy = (data->p3d.pos_y - data->p3d.map_y)
			* data->p3d.ddy;
	}
	else
	{
		data->p3d.step_y = 1;
		data->p3d.sdy = (data->p3d.map_y + 1.0 - data->p3d.pos_y)
			* data->p3d.ddy;
	}
}

static void	get_ray_dirs(t_rc *data, int x)
{
	data->p3d.cx = 2 * x / (double)WIDTH - 1;
	data->p3d.ray_dx = data->p3d.dir_x + data->p3d.px * data->p3d.cx;
	data->p3d.ray_dy = data->p3d.dir_y + data->p3d.py * data->p3d.cx;
	data->p3d.map_x = (int)data->p3d.pos_x;
	data->p3d.map_y = (int)data->p3d.pos_y;
	if (data->p3d.ray_dx == 0)
		data->p3d.ddx = INFINITE;
	else
		data->p3d.ddx = fabs(1 / data->p3d.ray_dx);
	if (data->p3d.ddy == 0)
		data->p3d.ddy = INFINITE;
	else
		data->p3d.ddy = fabs(1 / data->p3d.ray_dy);
	data->p3d.hit = 0;
}

void	raycast(t_rc *data)
{
	int		x;

	memset(data->img_world->pixels, 0, data->img_world->width * data->img_world->height * 4); // Not allowed function!
	x = 0;
	while (x < WIDTH)
	{
		get_ray_dirs(data, x);
		get_side_dist(data);
		look_for_wall_loop(data);
		print_walls(data, x);
		x++;
	}
}
