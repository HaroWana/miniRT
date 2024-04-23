#include "miniRT.h"

void	amb(char **split, t_data *d)
{
	t_amb	a;
	char	**tmpcolor;

	if (split_count(split) != 3)
		ft_error("Error\nInvalid ambiant light data\n");
	
	if (!ft_isfloat(split[1]) || ratioinrange(split[1]))
		ft_error("Error\nInvalid ratio value for ambiant light\n");
	a.ratio = ft_atof(split[1]);

	tmpcolor = ft_split(split[2], ',');
	a.rgb = get_color(tmpcolor);
	
	d->amb = a;
	d->alight_count++;
	ft_arr_freer(tmpcolor);
}
