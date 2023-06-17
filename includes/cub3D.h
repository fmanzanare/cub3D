#ifndef CUB3D_H
# define CUB3D_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

//************************** DEFINITIONS *************************************//
# define WIDTH		1024
# define HEIGHT		512
# define P_SIZE		8
# define MAP_WIDTH	1024/4
# define MAP_HEIGHT	512/2
# define PI			3.14159265359
# define ALPHA_INC	0.1
# define MULT_DELTA	5

typedef struct s_player{
	double	x;
	double	y;
	double	dy;
	double	dx;
	double	alpha;
}	t_player;

typedef struct s_map {
	char			**map;
	int				height;
	int				width;
	char			*n_tex;
	char			*s_tex;
	char			*w_tex;
	char			*e_tex;
	unsigned int	f_hex;
	unsigned int	c_hex;
}	t_map;

typedef struct s_rc{
	mlx_t		*mlx;
	mlx_image_t	*img_p;
	mlx_image_t	*img_map;
	mlx_image_t	*img_h;
	t_player	player;
	t_map		*map;
	int			sq_size_x;
	int			sq_size_y;
}	t_rc;

typedef struct s_init {
	char	*in_route;
	char	**in_cnt;
	int		in_fd;
	int		n_tex_fd;
	int		s_tex_fd;
	int		w_tex_fd;
	int		e_tex_fd;
	char	*f_rgb;
	char	*c_rgb;
	t_map	*map;
}	t_init;

//*************************** FUNCTIONS **************************************//

// PARSER
void	arg_checker(int argc, char **argv, t_init *init);
void	init_vars(t_init *init);
void	map_reader(t_init *init);
int		check_texture(t_init *init, char *str);
int		check_colors(t_init *init, char *str);
char	*get_tex_or_color(char *str);
int		map_builder(t_init *init, int idx);
void	map_normalizer(t_init *init, int idx);
void	map_checker(t_init *init);
void	print_incnt(t_init *init);
void	get_colors(t_init *init);
void	check_texture_files(t_init *init);

#endif
