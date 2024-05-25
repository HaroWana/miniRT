#include "miniRT.h"

extern t_data	d;

int	cam(char **buf)
{
	t_cam	cam;
	char	**tmp_pos;
	char	**tmp_axe;

	if (split_count(buf) != 4)
		return (2);

	// Verifying and assigning Camera position
	tmp_pos = ft_split(buf[1], ',');
	if (!valid_pos(tmp_pos))
	{
		free_2D_arr(tmp_pos);
		return (5);
	}
	cam.pos = get_coor(tmp_pos);

	// Verifying and assigning Camera direction vector
	tmp_axe = ft_split(buf[2], ',');
	if (!vectinrange(tmp_axe))
	{
		free_2D_arrs(tmp_pos, tmp_axe, NULL, NULL);
		return (8);
	}
	cam.forward = get_coor(tmp_axe);
	normalize(&cam.forward);

	// Verifying and assigning Camera Field-Of-View
	if (!fovinrange(atoi(buf[3])))
	{
		free_2D_arrs(tmp_pos, tmp_axe, NULL, NULL);
		return (7);
	}
	cam.fov = (atoi(buf[3])) * (M_PI / 360);

	cam_init(&cam, d.env.height / d.env.width);
	d.cam = cam;
	d.cam_count++;
	
	free_2D_arrs(tmp_pos, tmp_axe, NULL, NULL);
	return (0);
}
