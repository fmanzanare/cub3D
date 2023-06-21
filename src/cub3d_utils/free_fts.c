#include "../../includes/cub3D.h"

void	end_game(t_rc *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(data->texs[i]);
		i++;
	}
	mlx_delete_image(data->mlx, data->img_bg);
	mlx_delete_image(data->mlx, data->img_world);
	mlx_delete_image(data->mlx, data->img_p);
	mlx_delete_image(data->mlx, data->img_map);
	mlx_delete_image(data->mlx, data->img_h);
	struct_free_ft(&data->init);
	mlx_terminate(data->mlx);
	exit(0);
}

void	free_matrix(char **arr)
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

static void	free_map_struct(t_map *map)
{
	if (map->map)
		free_matrix(map->map);
	if (map->n_tex)
		free(map->n_tex);
	if (map->s_tex)
		free(map->s_tex);
	if (map->w_tex)
		free(map->w_tex);
	if (map->e_tex)
		free(map->e_tex);
}

void	struct_free_ft(t_init *init)
{
	if (init->map)
		free_map_struct(init->map);
	if (init->in_cnt)
		free_matrix(init->in_cnt);
	if (init->f_rgb)
		free(init->f_rgb);
	if (init->c_rgb)
		free(init->c_rgb);
	if (init->in_fd)
		close(init->in_fd);
	free(init->map);
}
