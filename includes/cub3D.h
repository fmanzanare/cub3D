/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:08:08 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/13 18:16:03 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

//************************** DEFINITIONS *************************************//
# define WIDTH		1024
# define HEIGHT		512
# define P_SIZE		8
# define MAP_WIDTH	1024/4
# define MAP_HEIGHT	512/2
# define MAP_X		8
# define MAP_Y		8

typedef struct s_rc{
	mlx_t		*mlx;
	mlx_image_t	*img_p;
	mlx_image_t	*img_map;
	int			map_size;
}	t_rc;

//*************************** FUNCTIONS **************************************//

#endif
