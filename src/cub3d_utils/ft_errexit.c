#include "../../includes/cub3D.h"

void	ft_errexit(t_init *init, char *str)
{
	struct_free_ft(init);
	ft_putstr_fd(str, 2);
	exit(1);
}
