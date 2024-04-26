#include "miniRT.h"

extern t_data	d;

int	amb(char **split)
{
	t_amb	a;
	char	**tmp_color;

	if (split_count(split) != 3)
		return (2);
	
	// Verifying and assigning Ambiant Light intensity ratio
	if (!ft_isfloat(split[1]) || !ratioinrange(split[1]))
		return (3);
	a.ratio = ft_atof(split[1]);

	// Verifying and assigning Ambiant Light color;
	tmp_color = ft_split(split[2], ',');
	if (!valid_rgb(tmp_color))
	{
		ft_arr_freer(tmp_color);
		return (4);
	}
	a.rgb = get_color(tmp_color);	
	
	d.amb = a;
	d.alight_count++;
	ft_arr_freer(tmp_color);
	return (0);
}
