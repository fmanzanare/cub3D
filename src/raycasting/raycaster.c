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

int32_t	main(int argc, char **argv)
{
	t_rc		data;
	t_init		init;

	arg_checker(argc, argv, &init);
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init(&data, &init);
	ft_print_minimap(&data);
	mlx_image_to_window(data.mlx, data.img_map, 0, 0);
	mlx_image_to_window(data.mlx, data.img_p, data.player.x - 4, data.player.y - 4);
	mlx_image_to_window(data.mlx, data.img_h, 0, 0);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
