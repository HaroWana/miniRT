#include "miniRT.h"

void	lum(char **buf, t_data *d)
{
	t_lum	l;
	char	**tmp_pos;
	char	**tmp_color;

	if (split_count(buf) != 4)
		ft_error("Error\nInvalid light data\n");

	tmp_pos = ft_split(buf[1], ',');
	check_pos(d, tmp_pos);
	l.pos = get_coor(tmp_pos);

	if (!ft_isfloat(buf[2]) || ratioinrange(buf[2]))
		ft_error("Error\nincorrect ratio value for L\n");
	l.ratio = ft_atof(buf[2]);

	tmp_color = ft_split(buf[3], ',');
	l.rgb = get_color(tmp_color);

	d->lum = l;
	d->light_count++;
	free_all(tmp_pos, tmp_color, NULL, NULL);
}
