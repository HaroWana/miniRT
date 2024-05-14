#include "miniRT.h"

extern	t_data	d;

int	sp(char **buf)
{
	t_elem		*sp;
	char		**tmp_pos;
	char		**tmp_color;

	// Allocating memory and checking parameter count
	if ((sp = elem_init()) == NULL)
		return (9);
	if (split_count(buf) != 4)
		return (2);
	
	// Verifying and assigning Sphere psition
	tmp_pos = ft_split(buf[1], ',');
	if (!valid_pos(tmp_pos))
	{
		free_2D_arr(tmp_pos);
		return (5);
	}
	sp->pos = get_coor(tmp_pos);

	// Verifying and assigning Sphere radius
	if (!valid_radius(buf[2]))
	{
		free_2D_arr(tmp_pos);
		return (6);
	}
	sp->radius = atof(buf[2]) / 2;

	// Verifying and assigning Sphere color
	tmp_color = ft_split(buf[3], ',');
	if (!valid_rgb(tmp_color))
	{
		free_2D_arrs(tmp_pos, tmp_color, NULL, NULL);
		return (4);
	}
	sp->rgb = get_color(tmp_color);	

	free_2D_arrs(tmp_pos, tmp_color, NULL, NULL);
	shapes_addback(&d.shapes.spheres, sp, &d.shapes.sphere_nb);
	return (0);
}
