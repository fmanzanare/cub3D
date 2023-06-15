#include "../../includes/cub3D.h"

static void	map_parser(t_init *init)
{
	int	i;

	i = 0;
	while (init->in_cnt[i])
	{
		if (check_texture(init, init->in_cnt[i]))
		{
			i++;
			continue ;
		}
		else if (check_colors(init, init->in_cnt[i]))
		{
			i++;
			continue ;
		}
		// else if (check_map(init, init->in_cnt, i))
		//	break;
		i++;
	}
}

/* ******************************************** */
// TEMPORAL CHECKER FUNCTION!!!
static void	print_incnt(t_init *init, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s", init->in_cnt[i]);
		i++;
	}
	printf("\n");
	printf("North tex: %s\n", init->map->n_tex);
	printf("South tex: %s\n", init->map->s_tex);
	printf("West tex: %s\n", init->map->w_tex);
	printf("East tex: %s\n", init->map->e_tex);
	printf("\n");
	printf("F color: %s\n", init->f_rgb);
	printf("C color: %s\n", init->c_rgb);
}
/* ******************************************** */

void	map_reader(t_init *init)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (read(init->in_fd, &tmp, 1) > 0)
	{
		if (tmp == '\n')
			i++;
	}
	close(init->in_fd);
	init->in_cnt = malloc(sizeof(char *) * (i + 1));
	if (!init->in_cnt)
		ft_puterr_fd("Error\nNot enough memory available", 2, 1);
	init->in_fd = open(init->in_route, O_RDONLY);
	while (j < i)
	{
		init->in_cnt[j] = get_next_line(init->in_fd);
		j++;
	}
	map_parser(init);
	print_incnt(init, i); // TEMPORAL CHECKER FUNCTION!
}
