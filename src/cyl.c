#include "miniRT.h"

void	cyl(char **buf, t_data *d)
{
	t_elem	*cy;
	char	**tmp_pos;
	char	**tmp_axe;
	char	**tmpcolor;

	cy = elem_init();
	if (split_count(buf) != 6)
		ft_error("Error\nInvalid cylinder data\n");

	tmp_pos = ft_split(buf[1], ',');
	check_pos(d, tmp_pos);
	cy->pos = get_coor(tmp_pos);

	tmp_axe = ft_split(buf[2], ',');
	vectinrange(d, tmp_axe);
	cy->axe = normalized(get_coor(tmp_axe));

	check_radius(d, buf[3]);
	cy->radius = ft_atof(buf[3]) / 2;

	check_radius(d, buf[4]);
	cy->height = ft_atof(buf[4]);

	tmpcolor = ft_split(buf[5], ',');
	cy->rgb = get_color(tmpcolor);

	free_all(tmp_pos, tmp_axe, tmpcolor, NULL);
	shapes_addback(&d->shapes.cylindres, cy, &d->shapes.cyl_nb);
}
