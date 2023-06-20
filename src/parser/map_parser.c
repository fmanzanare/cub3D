#include "../../includes/cub3D.h"

static void	close_fds(t_init *init)
{
	close(init->n_tex_fd);
	close(init->s_tex_fd);
	close(init->w_tex_fd);
	close(init->e_tex_fd);
}

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
		else if (map_builder(init, i))
			break ;
		i++;
	}
	check_texture_files(init);
	close_fds(init);
}

/* ******************************************** */
// TEMPORAL CHECKER FUNCTION!!!
void	print_incnt(t_init *init)
{
	int	i;

	printf("North tex: %s\n", init->map->n_tex);
	printf("South tex: %s\n", init->map->s_tex);
	printf("West tex: %s\n", init->map->w_tex);
	printf("East tex: %s\n", init->map->e_tex);
	printf("\n");
	printf("F color: %s\n", init->f_rgb);
	printf("F hex color: 0x%X\n", init->map->f_hex);
	printf("C color: %s\n", init->c_rgb);
	printf("C hex color: 0x%X\n", init->map->c_hex);
	printf("\n");
	i = 0;
	while (init->map->map[i])
	{
		printf("%s\n", init->map->map[i]);
		i++;
	}
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
		ft_errexit(init, "Error\nNot enough memory available");
	init->in_fd = open(init->in_route, O_RDONLY);
	while (j < i)
	{
		init->in_cnt[j] = get_next_line(init->in_fd);
		j++;
	}
	map_parser(init);
	get_colors(init);
	print_incnt(init); // TEMPORAL CHECKER FUNCTION!
}
