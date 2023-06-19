#include "../../includes/cub3D.h"

static void	check_side(t_rc *data)
{
	if (data->p3d.side == 0 && (data->p3d.map_x - data->p3d.pos_x) >= 0)
		data->p3d.side += 2;
	if (data->p3d.side == 1 && (data->p3d.map_y - data->p3d.pos_y) >= 0)
		data->p3d.side += 2;
}

static void	print_lines(t_rc * data, int x)
{
	int		i;
	uint8_t	*p;

	data->p3d.tex_x = (int)(data->p3d.wall_x * (double)data->texs[data->p3d.side]->width);
	data->p3d.tex_x = data->texs[data->p3d.side]->width - data->p3d.tex_x - 1;
	data->p3d.step = 1.0 * data->texs[data->p3d.side]->height / data->p3d.line_height;
	data->p3d.tex_pos = (data->p3d.draw_start - HEIGHT / 2 + data->p3d.line_height / 2) * data->p3d.step;
	i = data->p3d.draw_start;
	while (i < data->p3d.draw_end)
	{
		data->p3d.tex_y = (int)data->p3d.tex_pos;
		data->p3d.tex_pos += data->p3d.step;
		p = &data->texs[data->p3d.side]->pixels[data->texs[data->p3d.side]->width * data->p3d.tex_y * 4 + data->p3d.tex_x * 4];
		data->p3d.color = (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
		mlx_put_pixel(data->img_world, x, i, data->p3d.color);
		i++;
	}
}

void	put_textures(t_rc *data, int x)
{
	if (data->p3d.side == 0)
		data->p3d.wall_x = data->p3d.pos_y + data->p3d.perp_wall_dist * data->p3d.ray_dir_y;
	else
		data->p3d.wall_x = data->p3d.pos_x + data->p3d.perp_wall_dist * data->p3d.ray_dir_x;
	data->p3d.wall_x -= floor(data->p3d.wall_x);
	check_side(data);
	print_lines(data, x);
}
