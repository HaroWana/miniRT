#include "miniRT.h"

extern t_data	d;

int	lum(char **buf)
{
	t_lum	l;
	char	**tmp_pos;
	char	**tmp_color;

	if (split_count(buf) != 4)
		return (2);

	// Verifying and assigning Light source position
	tmp_pos = ft_split(buf[1], ',');
	if (!valid_pos(tmp_pos) || split_count(tmp_pos) != 3)
	{
		ft_arr_freer(tmp_pos);
		return (5);
	}
	l.pos = get_coor(tmp_pos);

	// Verifying and assigning Light source intensity ratio
	if (!ft_isfloat(buf[2]) || ratioinrange(buf[2]))
	{
		ft_arr_freer(tmp_pos);
		return (3);
	}
	l.ratio = ft_atof(buf[2]);

	// Verifying and assigning Light source color
	tmp_color = ft_split(buf[3], ',');
	l.rgb = get_color(tmp_color);
	if (split_count(tmp_color) != 3 || l.rgb < 0)
		return (4);

	d.lum = l;
	d.light_count++;
	free_all(tmp_pos, tmp_color, NULL, NULL);
	return (0);
}
