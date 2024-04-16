#include "miniRT.h"

void	ft_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
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

int	close_hook(t_data *d, int code)
{
	(void)d;
	if (code == 0)
		exit(EXIT_SUCCESS);
	else
		exit (EXIT_FAILURE);
}
