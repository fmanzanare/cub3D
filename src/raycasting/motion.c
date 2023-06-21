#include "../../includes/cub3D.h"

void	ft_lateral_3d_displacement(t_rc *data, char type)
{
	if (type == 'A')
	{
		ft_is_wall(data, data->player.y - data->player.dx,
			data->player.x + data->player.dy, 'A');
		if (data->map->map[(int)data->p3d.pos_y]
			[(int)(data->p3d.pos_x + data->p3d.dir_y * 0.1)] != '1')
			data->p3d.pos_x += data->p3d.dir_y * 0.1;
		if (data->map->map[(int)(data->p3d.pos_y - data->p3d.dir_x * 0.1)]
			[(int)data->p3d.pos_x] != '1')
			data->p3d.pos_y -= data->p3d.dir_x * 0.1;
	}
	else if (type == 'D')
	{
		ft_is_wall(data, data->player.y + data->player.dx,
			data->player.x - data->player.dy, 'D');
		if (data->map->map[(int)data->p3d.pos_y]
			[(int)(data->p3d.pos_x - data->p3d.dir_y * 0.1)] != '1')
			data->p3d.pos_x -= data->p3d.dir_y * 0.1;
		if (data->map->map[(int)(data->p3d.pos_y + data->p3d.dir_x * 0.1)]
			[(int)data->p3d.pos_x] != '1')
			data->p3d.pos_y += data->p3d.dir_x * 0.1;
	}
}

void	ft_3d_displacement(t_rc *data, char type)
{
	if (type == 'W')
	{
		ft_is_wall(data, data->player.y + data->player.dy,
			data->player.x + data->player.dx, 'W');
		if (data->map->map[(int)data->p3d.pos_y]
			[(int)(data->p3d.pos_x + data->p3d.dir_x * 0.1)] != '1')
			data->p3d.pos_x += data->p3d.dir_x * 0.1;
		if (data->map->map[(int)(data->p3d.pos_y + data->p3d.dir_y * 0.1)]
			[(int)data->p3d.pos_x] != '1')
			data->p3d.pos_y += data->p3d.dir_y * 0.1;
	}
	else if (type == 'S')
	{
		ft_is_wall(data, data->player.y - data->player.dy,
			data->player.x - data->player.dx, 'S');
		if (data->map->map[(int)data->p3d.pos_y]
			[(int)(data->p3d.pos_x - data->p3d.dir_x * 0.1)] != '1')
			data->p3d.pos_x -= data->p3d.dir_x * 0.1;
		if (data->map->map[(int)(data->p3d.pos_y - data->p3d.dir_y * 0.1)]
			[(int)data->p3d.pos_x] != '1')
			data->p3d.pos_y -= data->p3d.dir_y * 0.1;
	}
	ft_lateral_3d_displacement(data, type);
}

void	ft_lateral_mv(t_rc *data, char type)
{
	char	**map;
	int		sum_y;
	int		sum_x;
	int		y_index;
	int		x_index;

	sum_y = data->player.sum_y;
	sum_x = data->player.sum_x;
	y_index = data->player.y_index;
	x_index = data->player.x_index;
	map = data->map->map;
	if (map[y_index][sum_x] != '1' && type == 'A')
		data->player.x += data->player.dy;
	if (map[sum_y][x_index] != '1' && type == 'A')
		data->player.y -= data->player.dx;
	if (map[y_index][sum_x] != '1' && type == 'D')
		data->player.x -= data->player.dy;
	if (map[sum_y][x_index] != '1' && type == 'D')
		data->player.y += data->player.dx;
}
