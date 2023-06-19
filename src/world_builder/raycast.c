#include "../../includes/cub3D.h"

void	raycast(t_rc *data)
{
	data->p3d.pos_x = (data->player.x / data->sq_size_x);
	data->p3d.pos_y = (data->player.y / data->sq_size_y);

	memset(data->img_world->pixels, 0, data->img_world->width * data->img_world->height * 4);
	int		x = 0;
	while (x < WIDTH)
	{
		data->p3d.camera_x = 2 * x / (double)WIDTH - 1;
		data->p3d.ray_dir_x = data->p3d.dir_x + data->p3d.px * data->p3d.camera_x;
		data->p3d.ray_dir_y = data->p3d.dir_y + data->p3d.py * data->p3d.camera_x;

		data->p3d.map_x = (int)data->p3d.pos_x;
		data->p3d.map_y = (int)data->p3d.pos_y;

		data->p3d.delta_dist_x = (data->p3d.ray_dir_x == 0) ? INFINITE : fabs(1 / data->p3d.ray_dir_x);
		data->p3d.delta_dist_y = (data->p3d.ray_dir_y == 0) ? INFINITE : fabs(1 / data->p3d.ray_dir_y);

		data->p3d.hit = 0;

		if (data->p3d.ray_dir_x < 0)
		{
			data->p3d.step_x = -1;
			data->p3d.side_dist_x = (data->p3d.pos_x - data->p3d.map_x) * data->p3d.delta_dist_x;
		}
		else
		{
			data->p3d.step_x = 1;
			data->p3d.side_dist_x = (data->p3d.map_x + 1.0 - data->p3d.pos_x) * data->p3d.delta_dist_x;
		}

		if (data->p3d.ray_dir_y < 0)
		{
			data->p3d.step_y = -1;
			data->p3d.side_dist_y = (data->p3d.pos_y - data->p3d.map_y) * data->p3d.delta_dist_y;
		}
		else
		{
			data->p3d.step_y = 1;
			data->p3d.side_dist_y = (data->p3d.map_y + 1.0 - data->p3d.pos_y) * data->p3d.delta_dist_y;
		}

		while (data->p3d.hit == 0)
		{
			if (data->p3d.side_dist_x < data->p3d.side_dist_y)
			{
				data->p3d.side_dist_x += data->p3d.delta_dist_x;
				data->p3d.map_x += data->p3d.step_x;
				data->p3d.side = 0;
			}
			else
			{
				data->p3d.side_dist_y += data->p3d.delta_dist_y;
				data->p3d.map_y += data->p3d.step_y;
				data->p3d.side = 1;
			}
			if (data->map->map[data->p3d.map_y][data->p3d.map_x] == '1')
				data->p3d.hit = 1;
		}

		if (data->p3d.side == 0)
			data->p3d.perp_wall_dist = (data->p3d.side_dist_x - data->p3d.delta_dist_x);
		else
			data->p3d.perp_wall_dist = (data->p3d.side_dist_y - data->p3d.delta_dist_y);

		data->p3d.line_height = (int)(HEIGHT / data->p3d.perp_wall_dist);
		data->p3d.draw_start = (data->p3d.line_height * -1) / 2 + HEIGHT / 2;
		if (data->p3d.draw_start < 0)
			data->p3d.draw_start = 0;
		data->p3d.draw_end = data->p3d.line_height / 2 + HEIGHT / 2;
		if (data->p3d.draw_end >= HEIGHT)
			data->p3d.draw_end = HEIGHT - 1;

		data->p3d.color = 0x1AEB51FF;
		if (data->p3d.side == 1)
			data->p3d.color = 0x417A50FF;

		int	i = data->p3d.draw_start;
		while (i <= data->p3d.draw_end)
		{
			mlx_put_pixel(data->img_world, x, i, data->p3d.color);
			i++;
		}
		x++;
	}
}
