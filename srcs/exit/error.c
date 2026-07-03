#include "../../includes/cub3d.h"

int	err_msg(char *detail, char *msg, int code)
{
	ft_putstr_fd("Error\n", 2);
	if (detail && detail[0])
	{
		ft_putstr_fd(detail, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	return (code);
}
