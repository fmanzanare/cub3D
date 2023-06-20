#include "../../includes/cub3D.h"

int	ft_atoi_checker(const char *str, t_init *init)
{
	int			num;
	int			sign;

	sign = 1;
	num = 0;
	if (!*str)
		ft_errexit(init, "Error\nEmpty string.\n");
	while (ft_isspecialchar(*str))
		str++;
	if (ft_issign(*str) == -1)
		sign = -1;
	if (ft_issign(*str))
		str++;
	while (*str)
	{
		num = num * 10 + (*str - '0');
		if (!ft_isdigit(*str))
			ft_errexit(init, "Error\nNot numeric value for RGB.\n");
		str++;
	}
	num *= sign;
	return (num);
}
