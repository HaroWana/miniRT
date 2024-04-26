#include "miniRT.h"

extern t_data	d;

int	pl(char **buf)
{
	t_elem	*pl;
	char	**tmp_pos;
	char	**tmp_axe;
	char	**tmp_color;

	// Allocating memory and checking parameter count
	if ((pl = elem_init()) == NULL)
		return (9);
	if (split_count(buf) != 4)
		return (2);
	
	// Verifying and assigning Plane position
	tmp_pos = ft_split(buf[1], ',');
	if (!valid_pos(tmp_pos))
	{
		ft_arr_freer(tmp_pos);
		return (5);
	}
	pl->pos = get_coor(tmp_pos);

	// Verifying and assigning Plane normal vector
	tmp_axe = ft_split(buf[2], ',');
	if (!vectinrange(tmp_axe))
	{
		free_all(tmp_pos, tmp_axe, NULL, NULL);
	}
	pl->normal = get_coor(tmp_axe);
	
	// Verifying and assigning Plane color
	tmp_color = ft_split(buf[3], ',');
	if (!valid_rgb(tmp_color))
	{
		free_all(tmp_pos, tmp_axe, tmp_color, NULL);
		return (4);
	}
	pl->rgb = get_color(tmp_color);	

	free_all(tmp_pos, tmp_axe, tmp_color, NULL);
	shapes_addback(&d.shapes.planes, pl, &d.shapes.plane_nb);
	return (0);
}
