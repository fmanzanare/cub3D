/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_catcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:03:16 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/21 19:03:17 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_texture_files(t_init *init)
{
	if (open(init->map->n_tex, O_RDONLY) < 0)
		ft_errexit(init, "Error\nNorth texture file not found.\n");
	else if (open(init->map->s_tex, O_RDONLY) < 0)
		ft_errexit(init, "Error\nSouth texture file not found.\n");
	else if (open(init->map->w_tex, O_RDONLY) < 0)
		ft_errexit(init, "Error\nWest texture file not found.\n");
	else if (open(init->map->e_tex, O_RDONLY) < 0)
		ft_errexit(init, "Error\nEast texture file not found.\n");
}

char	*get_tex_or_color(char *str)
{
	char	*ret;
	int		i;

	str += 2;
	i = 0;
	while (ft_isspecialchar(*str))
		str++;
	ret = malloc(sizeof(char) * (ft_strlen(str)));
	while (*str && *str != '\n')
	{
		ret[i] = *str;
		i++;
		str++;
	}
	ret[i] = '\0';
	return (ret);
}

static void	check_dup_textures(t_init *init, int opc)
{
	if (opc == 1 && init->map->n_tex)
		ft_errexit(init, "Error\nMore than one texture for North.\n");
	else if (opc == 2 && init->map->s_tex)
		ft_errexit(init, "Error\nMore than one texture for South.\n");
	if (opc == 3 && init->map->w_tex)
		ft_errexit(init, "Error\nMore than one texture for West.\n");
	if (opc == 4 && init->map->e_tex)
		ft_errexit(init, "Error\nMore than one texture for East.\n");
}

static int	check_cardinal(t_init *init, char *str)
{
	if (*str == 'N' && str[1] == 'O')
	{
		check_dup_textures(init, 1);
		init->map->n_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'S' && str[1] == 'O')
	{
		check_dup_textures(init, 2);
		init->map->s_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'W' && str[1] == 'E')
	{
		check_dup_textures(init, 3);
		init->map->w_tex = get_tex_or_color(str);
		return (1);
	}
	else if (*str == 'E' && str[1] == 'A')
	{
		check_dup_textures(init, 4);
		init->map->e_tex = get_tex_or_color(str);
		return (1);
	}
	return (0);
}

int	check_texture(t_init *init, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != '\n')
	{
		while (ft_isspecialchar(*tmp))
			tmp++;
		if (check_cardinal(init, tmp))
			return (1);
		tmp++;
	}
	return (0);
}
