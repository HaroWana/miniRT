#include "miniRT.h"

int	rgbinrange(int nb)
{
	if (nb >= 0 && nb <= 255)
		return (0);
	else
		return (1);
}

void	vectinrange(t_data *d, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atof(str[i]) < -1 || ft_atof(str[i]) > 1 || !ft_isfloat(str[i]))
		{
			close(d->fd);
			ft_error("Error\nVector non-numerical or out of range\n");
		}
		i++;
	}
}

int	ratioinrange(char *ratio)
{
	if (ft_atof(ratio) >= 0 && ft_atof(ratio) <= 1)
		return (0);
	else
		return (1);
}

int	fovinrange(int nb)
{
	if (nb >= 0 && nb <= 180)
		return (0);
	else
		return (1);
}

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i] && *split[i])
		i++;
	return (i);
}
