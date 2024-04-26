#include "miniRT.h"

bool	rgbinrange(int nb)
{
	if (nb >= 0 && nb <= 255)
		return (true);
	else
		return (false);
}

bool	vectinrange(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atof(str[i]) < -1 || ft_atof(str[i]) > 1 || !ft_isfloat(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ratioinrange(char *ratio)
{
	if (ft_atof(ratio) >= 0 && ft_atof(ratio) <= 1)
		return (true);
	else
		return (false);
}

bool	fovinrange(int nb)
{
	if (nb >= 0 && nb <= 180)
		return (true);
	else
		return (false);
}

bool	valid_pos(char **pos)
{
	if (ft_isfloat(pos[0]) == false || ft_isfloat(pos[1]) == false
		|| ft_isfloat(pos[2]) == false)
	{
		return (false);
	}
	return (true);
}

bool	valid_radius(char *radius)
{
	if (ft_isfloat(radius) == false || ft_atof(radius) < 0)
	{
		return (false);
	}
	return (true);
}

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i] && *split[i])
		i++;
	return (i);
}
