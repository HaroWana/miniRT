#include "miniRT.h"

extern t_data 	d;

void	clean_up()
{
	t_elem	*tmp;

	while (d.shapes.spheres)
	{
		tmp = d.shapes.spheres;
		d.shapes.spheres = d.shapes.spheres->next;
		free(tmp);
		tmp = NULL;
	}
	while (d.shapes.planes)
	{
		tmp = d.shapes.planes;
		d.shapes.planes = d.shapes.planes->next;
		free(tmp);
		tmp = NULL;
	}
	while (d.shapes.cylindres)
	{
		tmp = d.shapes.cylindres;
		d.shapes.cylindres = d.shapes.cylindres->next;
		free(tmp);
		tmp = NULL;
	}
	if (d.env.mlx)
		mlx_terminate(d.env.mlx);
}

static void	free_strs(char **tmp, char **tmp_pos, char **tmp_axe,
	char **tmpcolor)
{
	int	i;

	i = 0;
	if (tmp)
		while (tmp[i])
			free (tmp[i++]);
	i = 0;
	if (tmp_pos)
		while (tmp_pos[i])
			free (tmp_pos[i++]);
	i = 0;
	if (tmp_axe)
		while (tmp_axe[i])
			free (tmp_axe[i++]);
	i = 0;
	if (tmpcolor)
		while (tmpcolor[i])
			free(tmpcolor[i++]);
}

void	free_all(char **tmp, char **tmp_pos, char **tmp_axe, char **tmpcolor)
{
	free_strs(tmp, tmp_pos, tmp_axe, tmpcolor);
	if (tmp_pos)
	{
		free(tmp_pos);
		tmp_pos = NULL;
	}
	if (tmp_axe)
	{
		free(tmp_axe);
		tmp_axe = NULL;
	}
	if (tmpcolor)
	{
		free(tmpcolor);
		tmpcolor = NULL;
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}

int	close_hook(t_data *d, int code) // necessary ?
{
	(void)d;
	if (code == 0)
		exit(EXIT_SUCCESS);
	else
		exit (EXIT_FAILURE);
}
