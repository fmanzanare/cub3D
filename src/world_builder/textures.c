/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:02:28 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/21 19:02:29 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	check_side(t_rc *data)
{
	if (data->p3d.side == 0 && (data->p3d.map_x - data->p3d.pos_x) >= 0)
		data->p3d.side += 2;
	if (data->p3d.side == 1 && (data->p3d.map_y - data->p3d.pos_y) >= 0)
		data->p3d.side += 2;
}

static void	print_lines(t_rc *data, int x)
{
	int		i;
	uint8_t	*p;
	int		side;

	side = data->p3d.side;
	data->p3d.tx = (int)(data->p3d.wall_x * (double)data->texs[side]->width);
	data->p3d.tx = data->texs[side]->width - data->p3d.tx - 1;
	data->p3d.step = 1.0 * data->texs[side]->height / data->p3d.l_height;
	data->p3d.tpos = (data->p3d.d_start - HEIGHT / 2 + data->p3d.l_height / 2)
		* data->p3d.step;
	i = data->p3d.d_start;
	while (i < data->p3d.d_end)
	{
		data->p3d.ty = (int)data->p3d.tpos;
		data->p3d.tpos += data->p3d.step;
		p = &data->texs[side]->pixels[data->texs[side]->width
			* data->p3d.ty * 4 + data->p3d.tx * 4];
		data->p3d.color = (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
		mlx_put_pixel(data->img_world, x, i, data->p3d.color);
		i++;
	}
}

void	put_textures(t_rc *data, int x)
{
	if (data->p3d.side == 0)
		data->p3d.wall_x = data->p3d.pos_y + data->p3d.pwd * data->p3d.ray_dy;
	else
		data->p3d.wall_x = data->p3d.pos_x + data->p3d.pwd * data->p3d.ray_dx;
	data->p3d.wall_x -= floor(data->p3d.wall_x);
	check_side(data);
	print_lines(data, x);
}
