/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:55:51 by vde-prad          #+#    #+#             */
/*   Updated: 2023/06/26 17:04:17 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	ft_put_image(t_rc *data)
{
	int	x_map;
	int	y_map;

	x_map = (MAP_WIDTH / 2) - (8 / 2);
	y_map = (MAP_HEIGHT / 2) - (8 / 2);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_p, x_map, y_map);
	mlx_image_to_window(data->mlx, data->img_h, 0, 0);
}

void	ft_print_player(t_rc *data)
{
	int	*pointer;
	int	p;

	p = 0;
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
}

int	main(int argc, char **argv)
{
	t_rc		data;

	arg_checker(argc, argv, &data.init);
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init(&data, &data.init);
	world_builder(&data);
	png_to_textures(&data);
	raycast(&data);
	mlx_image_to_window(data.mlx, data.img_bg, 0, 0);
	mlx_image_to_window(data.mlx, data.img_world, 0, 0);
	ft_put_image(&data);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
