#include "../includes/cub3D.h"

#define BPP sizeof(int32_t)

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;

	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	else if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img->instances[0].y -= 5;
	else if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img->instances[0].y += 5;
	else if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img->instances[0].x -= 5;
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img->instances[0].x += 5;
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	main(void)
{
	t_rc		data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, 8, 8);
	memset(data.img->pixels, 255, data.img->width * data.img->height * BPP);
	int *pointer = (int*)data.img->pixels;
	for (unsigned int p = 0; p < data.img->width * data.img->height; p++) {
		pointer[p] = 0xFF00FFFF;
	}
	mlx_image_to_window(data.mlx, data.img, WIDTH/2 -32, HEIGHT/2 - 32);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
