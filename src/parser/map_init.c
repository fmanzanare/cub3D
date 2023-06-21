/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:03:06 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/21 19:03:06 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_map_vars(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->n_tex = NULL;
	map->s_tex = NULL;
	map->w_tex = NULL;
	map->e_tex = NULL;
	map->f_hex = 0;
	map->c_hex = 0;
}

void	init_vars(t_init *init)
{
	init->in_route = NULL;
	init->in_cnt = NULL;
	init->in_fd = 0;
	init->n_tex_fd = 0;
	init->s_tex_fd = 0;
	init->w_tex_fd = 0;
	init->e_tex_fd = 0;
	init->f_rgb = NULL;
	init->c_rgb = NULL;
	init->map = malloc(sizeof(t_map));
	init_map_vars(init->map);
}
