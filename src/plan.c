#include "miniRT.h"

void	pl(char **buf, t_data *d)
{
	t_elem	*pl;
	char	**tmp_pos;
	char	**tmp_axe;
	char	**tmp_color;

	pl = elem_init();
	if (split_count(buf) != 4)
		ft_error("Error\nInvalid plane data\n");
	
	// Weird
	tmp_pos = ft_split(buf[1], ',');
	check_pos(d, tmp_pos);
	pl->pos = get_coor(tmp_pos);

	tmp_axe = ft_split(buf[2], ',');
	vectinrange(d, tmp_axe);

	pl->normal = get_coor(tmp_axe);
	
	tmp_color = ft_split(buf[3], ',');
	pl->rgb = get_color(tmp_color);

	free_all(tmp_pos, tmp_axe, tmp_color, NULL);
	shapes_addback(&d->shapes.planes, pl, &d->shapes.plane_nb);
}
