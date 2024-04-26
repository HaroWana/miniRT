#include "miniRT.h"

float	sqr(float f)
{
	return (f * f);
}

int	get_color(char **split)
{
	int	res;
	int	color;
	int	i;

	i = 0;
	res = 0;
	
	while (split[i])
	{
		if (!ft_isint(split[i]))
			return (-1);
		color = ft_atoi(split[i]);
		if (!ft_isrgb(color))
			return (-1);
		res = (res << 8) | color;
		i++;
	}
	res = (res << 8) | 255;
	return (res);
}
