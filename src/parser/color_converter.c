#include "../../includes/cub3D.h"

static int	array_len(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

static void	free_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static unsigned int get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	get_rgb_ints(t_init *init, char **rgb, int opc)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_puterr_fd("Error\nWrong value for red\n", 2, 1);
	if (opc == 1)
		init->map->f_hex = get_rgb(r, g, b, 255);
	else if (opc == 2)
		init->map->c_hex = get_rgb(r, g, b, 255);
}

void	get_colors(t_init *init)
{
	char	**rgb;

	rgb = ft_split(init->f_rgb, ',');
	if (array_len(rgb) != 3)
		ft_puterr_fd("Error\nWrong RGB for Floor\n", 2, 1);
	get_rgb_ints(init, rgb, 1);
	free_matrix(rgb);
	rgb = ft_split(init->c_rgb, ',');
	if (array_len(rgb) != 3)
		ft_puterr_fd("Error\nWrong RGB for Floor\n", 2, 1);
	get_rgb_ints(init, rgb, 2);
	free_matrix(rgb);
}
