#include "miniRT.h"

extern t_data	d;

int	cyl(char **buf)
{
	t_elem	*cy;
	char	**tmp_pos;
	char	**tmp_axe;
	char	**tmp_color;

	// Allocating memory and checking parameter count
	if ((cy = elem_init()) == NULL)
		return (9);
	if (split_count(buf) != 6)
		return (2);

	// Verifying and assigning Cylindre position
	tmp_pos = ft_split(buf[1], ',');
	if (!valid_pos(tmp_pos))
	{
		ft_arr_freer(tmp_pos);
		return (5);
	}
	cy->pos = get_coor(tmp_pos);

	// Verifying and assigning Cylindre	direction
	tmp_axe = ft_split(buf[2], ',');
	if (!vectinrange(tmp_axe))
	{
		free_all(tmp_pos, tmp_axe, NULL, NULL);
		return (8);
	}
	cy->axe = normalized(get_coor(tmp_axe));

	// Verifying and assigning Cylindre height and radius
	if (!valid_radius(buf[3]) || !valid_radius(buf[4]))
	{
		free_all(tmp_pos, tmp_axe, NULL, NULL);
		return (6);
	}
	cy->radius = ft_atof(buf[3]) / 2;
	cy->height = ft_atof(buf[4]);

	// Verifying and assigning Cylindre color
	tmp_color = ft_split(buf[5], ',');
	if (!valid_rgb(tmp_color))
	{
		free_all(tmp_pos, tmp_axe, tmp_color, NULL);
		return (4);
	}
	cy->rgb = get_color(tmp_color);	

	free_all(tmp_pos, tmp_axe, tmp_color, NULL);
	shapes_addback(&d.shapes.cylindres, cy, &d.shapes.cyl_nb);
	return (0);
}
