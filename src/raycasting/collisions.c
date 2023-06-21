#include "../../includes/cub3D.h"

static int	ft_check_index(t_rc *data, int y, int x)
{
	if (y > data->map->height || y < 0)
		return (1);
	if (x > data->map->width || x < 0)
		return (1);
	return (0);
}

int	is_wall(t_rc *data, double py, double px)
{
	int	x;
	int	y;

	x = (int)px / PIX_SQ;
	y = (int)py / PIX_SQ;
	if (ft_check_index(data, y, x))
		return (1);
	return (data->map->map[y][x] == '1');
}

void	ft_is_wall(t_rc *data, double py, double px, char type)
{
	char	**map;

	map = data->map->map;
	data->player.y_index = (int)data->player.y / PIX_SQ;
	data->player.x_index = (int)data->player.x / PIX_SQ;
	data->player.sum_y = (int)py / PIX_SQ;
	data->player.sum_x = (int)px / PIX_SQ;
	if (ft_check_index(data, data->player.y_index, data->player.x_index))
		return ;
	else if (ft_check_index(data, data->player.sum_y, data->player.sum_x))
		return ;
	if (map[data->player.y_index][data->player.sum_x] != '1' && type == 'W')
		data->player.x += data->player.dx;
	if (map[data->player.sum_y][data->player.x_index] != '1' && type == 'W')
		data->player.y += data->player.dy;
	if (map[data->player.y_index][data->player.sum_x] != '1' && type == 'S')
		data->player.x -= data->player.dx;
	if (map[data->player.sum_y][data->player.x_index] != '1' && type == 'S')
		data->player.y -= data->player.dy;
	ft_lateral_mv(data, type);
}
