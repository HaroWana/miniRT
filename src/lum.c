#include "miniRT.h"

void	lum(char *buf, t_data *d)
{
	t_lum	l;
	char	**tmp;
	char	**tmp_pos;
	char	**tmpcolor;

	tmp = ft_split2(buf, d);
	if (split_count(tmp) != 4)
		ft_error("Error\nInvalid light data\n");
	tmp_pos = ft_split(tmp[1], ',');
	check_pos(d, tmp_pos);
	l.pos = get_coor(tmp_pos);
	if (!ft_isfloat(tmp[2]) || ratioinrange(tmp[2]))
		ft_error("Error\nincorrect ratio value for L\n");
	l.ratio = ft_atof(tmp[2]);
	tmpcolor = ft_split(tmp[3], ',');
	l.rgb = get_color(tmpcolor);
	free_all(tmp, tmp_pos, tmpcolor, NULL);
	d->lum = l;
	d->light_count++;
}
