/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:03:02 by fmanzana          #+#    #+#             */
/*   Updated: 2023/06/21 19:03:02 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_valid_elem(char c)
{
	if (c == '1' || c == '0')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	else
		return (0);
}

static void	check_adjacents(t_init *init, char *line, int i, int idx)
{
	if (!line[i])
		return ;
	if (!check_valid_elem(line[i]))
		ft_errexit(init, "Error\nWrong elements on map.\n");
	if (line[i] != '1')
	{
		if ((!line[i + 1] || line[i + 1] == '.')
			|| (!idx || idx == init->map->height - 1)
			|| (idx > 0 && !check_valid_elem(init->map->map[idx - 1][i]))
			|| (idx < init->map->height - 1
				&& !check_valid_elem(init->map->map[idx + 1][i])))
			ft_errexit(init, "Error\nWrong map configuration\n");
	}
}

static void	line_checker(t_init *init, char *line, int idx)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '.')
		{
			while (line[i] == '.')
				i++;
			if (!line[i])
				continue ;
			else if (line[i] != '1')
				ft_errexit(init, "Error\nWrong map configuration\n");
		}
		check_adjacents(init, line, i, idx);
		i++;
	}
}

static int	check_player(t_init *init)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	j = 0;
	cnt = 0;
	while (init->map->map[i])
	{
		j = 0;
		while (init->map->map[i][j])
		{
			if (check_valid_elem(init->map->map[i][j]) == 2)
				cnt++;
			j++;
		}
		i++;
	}
	if (cnt == 1)
		return (1);
	else
		return (0);
}

void	map_checker(t_init *init)
{
	int	i;

	i = 0;
	if (!check_player(init))
		ft_errexit(init, "Error\nIssues with player positioning.\n");
	while (init->map->map[i])
	{
		line_checker(init, init->map->map[i], i);
		i++;
	}
}
