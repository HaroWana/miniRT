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
}

void	free_2D_arr(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_2D_arrs(char **tmp, char **tmp_pos, char **tmp_axe, char **tmpcolor)
{
	int	i = 0;	
	if (tmp)
	{
		while (tmp[i])
			free (tmp[i++]);
		free(tmp);
		tmp = NULL;
	}
	i = 0;
	if (tmp_pos)
	{
		while (tmp_pos[i])
			free (tmp_pos[i++]);
		free(tmp_pos);
		tmp_pos = NULL;
	}
	i = 0;
	if (tmp_axe)
	{
		while (tmp_axe[i])
			free (tmp_axe[i++]);
		free(tmp_axe);
		tmp_axe = NULL;
	}
	i = 0;
	if (tmpcolor)
	{
		while (tmpcolor[i])
			free (tmpcolor[i++]);
		free(tmpcolor);
		tmpcolor = NULL;
	}
}
