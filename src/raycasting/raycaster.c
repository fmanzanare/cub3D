#include "../../includes/cub3D.h"

// int	map[][8] =
// {
// 	{1,1,1,1,1,1,1,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,0,0,0,0,0,1,},
// 	{1,0,0,0,0,1,0,1,},
// 	{1,0,0,0,0,0,0,1,},
// 	{1,1,1,1,1,1,1,1,},
// };


static void	ft_put_image(t_rc *data)
{
	int	x_map;
	int	y_map;

	x_map = (MAP_WIDTH / 2) - (P_SIZE / 2);
	y_map = (MAP_HEIGHT / 2) - (P_SIZE / 2);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_p, x_map, y_map);
	mlx_image_to_window(data->mlx, data->img_h, 0, 0);
}

int32_t	main(int argc, char **argv)
{
	t_rc		data;
	t_init		init;

	arg_checker(argc, argv, &init);
	data.mlx = mlx_init(MAP_WIDTH, MAP_HEIGHT, "MLX42", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init(&data, &init);
	ft_put_image(&data);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}