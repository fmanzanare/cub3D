#include "../../includes/cub3D.h"

static void check_map_ext(char **argv)
{
	char	*route;
	int		len;
	int		flag;

	flag = 1;
	route = argv[1];
	len = ft_strlen(route) - 1;
	if (route[len] != 'b' || route[len - 1] != 'u'
		|| route[len - 2] != 'c' || route[len - 3] != '.')
		flag = 0;
	if (!flag)
		ft_puterr_fd("Error\nMap extension is wrong\n", 1, 1);
}

void	arg_checker(int argc, char **argv, t_init *init)
{
	if (argc != 2)
		ft_puterr_fd("Error\nOnly two arguments are accepted\n", 1, 1);
	check_map_ext(argv);
	init->input = argv[1];
	init->in_fd = open(argv[1], O_RDONLY);
	if (init->in_fd < 0)
		ft_puterr_fd("Error\nThe map file does not exist\n", 1, 1);
}
