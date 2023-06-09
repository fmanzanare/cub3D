/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:08:08 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/08 15:46:00 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

//************************** DEFINITIONS *************************************//
# define WIDTH 1024
# define HEIGHT 512
typedef struct s_rc{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_rc;

//*************************** FUNCTIONS **************************************//

#endif
