#include "miniRT.h"

void	check_pos(t_data *d, char **pos)
{
	if (ft_isfloat(pos[0]) == false || ft_isfloat(pos[1]) == false
		|| ft_isfloat(pos[2]) == false)
	{
		close(d->fd);
		ft_error("Error\nShape position is invalid\n");
	}
}

void	check_radius(t_data *d, char *radius)
{
	if (ft_isfloat(radius) == false || ft_atof(radius) < 0)
	{
		close(d->fd);
		ft_error("Error: Shape radius is invalid\n");
	}
}

void	sp(char **buf, t_data *d)
{
	t_elem		*sp;
	char		**tmp_pos;
	char		**tmp_color;

	sp = elem_init();
	if (split_count(buf) != 4)
		ft_error("Error: Invalid sphere data\n");
	
	tmp_pos = ft_split(buf[1], ',');
	check_pos(d, tmp_pos);
	sp->pos = get_coor(tmp_pos);

	check_radius(d, buf[2]);
	sp->radius = atof(buf[2]) / 2;

	tmp_color = ft_split(buf[3], ',');
	sp->rgb = get_color(tmp_color);

	free_all(tmp_pos, tmp_color, NULL, NULL);
	shapes_addback(&d->shapes.spheres, sp, &d->shapes.sphere_nb);
}
