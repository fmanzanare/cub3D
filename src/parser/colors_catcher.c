/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_catcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:02:46 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/21 19:02:47 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	check_dup_colors(t_init *init, int opc)
{
	if (opc == 1 && init->f_rgb)
		ft_errexit(init, "Error\nMore than one color for Floor.\n");
	else if (opc == 2 && init->c_rgb)
		ft_errexit(init, "Error\nMore than one color for Ceiling.\n");
}

static int	check_cf(t_init *init, char *str)
{
	if (*str == 'F')
	{
		check_dup_colors(init, 1);
		init->f_rgb = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'C')
	{
		check_dup_colors(init, 2);
		init->c_rgb = get_tex_or_color(str);
		return (1);
	}
	return (0);
}

int	check_colors(t_init *init, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != '\n')
	{
		while (ft_isspecialchar(*tmp))
			tmp++;
		if (check_cf(init, tmp))
			return (1);
		tmp++;
	}
	return (0);
}
