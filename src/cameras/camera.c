#include "miniRT.h"

static void	check_cam(t_cam c, t_data *d)
{
	if (fovinrange(c.fov))
	{
		close(d->fd);
		ft_error("Error\nFOV of camera not in the range\n");
	}
}

void	cam(char *buf, t_data *d)
{
	t_cam	cam;
	char	**tmp;
	char	**tmp_pos;
	char	**tmp_axe;

	tmp = ft_split2(buf, d);
	if (split_count(tmp) != 4)
		ft_error("Error\nInvalid cam data\n");
	tmp_pos = ft_split(tmp[1], ',');
	check_pos(d, tmp_pos);
	cam.pos = get_coor(tmp_pos);
	tmp_axe = ft_split(tmp[2], ',');
	vectinrange(d, tmp_axe);
	cam.forward = get_coor(tmp_axe);
	normalize(&cam.forward);
	cam.fov = ft_atoi(tmp[3]);
	check_cam(cam, d);
	cam.fov = (ft_atoi(tmp[3])) * (M_PI / 360);
	free_all(tmp, tmp_pos, tmp_axe, NULL);
	cam_init(&cam, d->env.size_y / d->env.size_x);
	d->cam = cam;
	d->cam_count++;
}
