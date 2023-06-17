#include "../../includes/cub3D.h"

void	raycast(t_rc *data)
{
	double	cx;
	double	ray_dir_x;
	double	ray_dir_y;
	int		x;

	// Map position (in matrix) to be checked if it is a wall.
	int		map_x;
	int		map_y;

	// Checks which (X or Y) has been hitted by the ray.
	int		side;

	// From current to next X or Y-side.
	double	side_dist_x;
	double	side_dist_y;

	// From one X or Y-side to next X or Y-side.
	double	next_x_side_dist;
	double	next_y_side_dist;

	// Ray direction after hitting an X or Y-side.
	int		step_x;
	int		step_y;

	// 1 if it ray hits a wall, 0 if not.
	int		hit;

	// Perpedicular Wall Distance.
	double	perp_wall_dist;

	// Contains the line height.
	int		line_height;

	// Contains the lowest and highest pixel to be drawn in current line.
	int		draw_start;
	int		draw_end;

	// Colors for wall sides.
	unsigned int	color;

	// Iterator for put_pixel function.
	int		i;

	data->player.px = 0;
	data->player.py = 0.66;

	memset(data->img_world->pixels, 0, data->img_world->width * data->img_world->height * 4);
	x = 0;
	while (x < WIDTH)
	{
		hit = 0;
		map_x = (int)(data->player.x / data->sq_size_x);
		map_y = (int)(data->player.y / data->sq_size_y);
		color = 0x2EE324FF;

		cx = 2 * x / (double)WIDTH - 1;
		ray_dir_x = data->player.dx + data->player.px * cx;
		ray_dir_y = data->player.dy + data->player.py * cx;

		if (!ray_dir_x)
			ray_dir_x = INFINITE;
		if (!ray_dir_y)
			ray_dir_y = INFINITE;
		next_x_side_dist = fabs(1 / ray_dir_x);
		next_y_side_dist = fabs(1 / ray_dir_y);

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = ((int)(data->player.x / data->sq_size_x) - map_x) * next_x_side_dist;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - (int)(data->player.x / data->sq_size_x)) * next_x_side_dist;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = ((int)(data->player.y / data->sq_size_y) - map_y) * next_y_side_dist;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - (int)(data->player.y / data->sq_size_y)) * next_y_side_dist;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += next_x_side_dist;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += next_y_side_dist;
				map_y += step_y;
				side = 1;
			}
			if (data->map->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - next_x_side_dist);
		else
			perp_wall_dist = (side_dist_y - next_y_side_dist);

		line_height = (int)(HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		if (side)
			color = 0x3f703dFF;

		i = draw_start;
		while (i <= draw_end)
		{
			mlx_put_pixel(data->img_world, x, i, color);
			i++;
		}
		x++;
	}
}
