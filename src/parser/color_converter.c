#include "../../includes/cub3D.h"

static int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static unsigned int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	get_rgb_ints(t_init *init, char **rgb, int opc)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi_checker(rgb[0], init);
	g = ft_atoi_checker(rgb[1], init);
	b = ft_atoi_checker(rgb[2], init);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_errexit(init, "Error\nWrong value for RGB\n");
	if (opc == 1)
		init->map->f_hex = get_rgb(r, g, b, 255);
	else if (opc == 2)
		init->map->c_hex = get_rgb(r, g, b, 255);
}

void	get_colors(t_init *init)
{
	char	**rgb;

	if (!init->f_rgb)
		ft_errexit(init, "Error\nFloor color not found\n");
	rgb = ft_split(init->f_rgb, ',');
	if (array_len(rgb) != 3)
		ft_errexit(init, "Error\nWrong RGB for Floor\n");
	get_rgb_ints(init, rgb, 1);
	free_matrix(rgb);
	if (!init->c_rgb)
		ft_errexit(init, "Error\nCeiling color not found\n");
	rgb = ft_split(init->c_rgb, ',');
	if (array_len(rgb) != 3)
		ft_errexit(init, "Error\nWrong RGB for Floor\n");
	get_rgb_ints(init, rgb, 2);
	free_matrix(rgb);
}
