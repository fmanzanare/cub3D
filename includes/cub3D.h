#ifndef CUB3D_H
# define CUB3D_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

//************************** DEFINITIONS *************************************//
# define WIDTH		1024
# define HEIGHT		512
# define P_SIZE		8
# define MAP_WIDTH	1024/4
# define MAP_HEIGHT	512/2
# define MAP_X		8
# define MAP_Y		8
# define PI			3.14159265359
# define ALPHA_INC	0.3
# define MULT_DELTA	10

typedef struct s_player{
	double	x;
	double	y;
	double	dy;
	double	dx;
	double	alpha;
}	t_player;
typedef struct s_rc{
	mlx_t		*mlx;
	mlx_image_t	*img_p;
	mlx_image_t	*img_map;
	mlx_image_t	*img_h;
	t_player	player;
}	t_rc;

//*************************** FUNCTIONS **************************************//

#endif
