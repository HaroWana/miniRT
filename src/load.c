#include "miniRT.h"

static void	load_data2(char *buf, t_data *d)
{
	char	**split;
	split = ft_split_words(buf);

	if (ft_strncmp(split[0], "A", 1) == 0 && ft_strlen(split[0]) == 1)
		amb(split, d);
	else if (ft_strncmp(split[0], "C", 1) == 0 && ft_strlen(split[0]) == 1)
		cam(split, d);
	else if (ft_strncmp(split[0], "L", 1) == 0 && ft_strlen(split[0]) == 1)
		lum(split, d);
	else if (ft_strncmp(split[0], "sp", 2) == 0 && ft_strlen(split[0]) == 2)
		sp(split, d);
	else if (ft_strncmp(split[0], "pl", 2) == 0 && ft_strlen(split[0]) == 2)
		pl(split, d);
	else if (ft_strncmp(split[0], "cy", 2) == 0 && ft_strlen(split[0]) == 2)
		cyl(split, d);
	else
	{
		printf("buf: %s", buf);
		close(d->fd);
		ft_arr_freer(split);
		ft_error("Error: Invalid data\n");
	}
	ft_arr_freer(split);
}

void	load_data(t_data *d, char *filename)
{
	char	*buf;

	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3) != 0)
		ft_error("Error: This program requires a .rt scene file.\n");
	d->fd = open(filename, O_RDONLY);
	if (d->fd < 0)
	{
		close(d->fd);
		ft_error("\x1B[31mError: Invalid file\n");
	}
	buf = get_next_line(d->fd);
	if (!buf)
		ft_error("Error: File is empty\n");
	while (buf)
	{
		if (*buf != '\n' && *buf != '\r')
			load_data2(buf, d);
		free(buf);
		buf = NULL;
		buf = get_next_line(d->fd);
	}
	close(d->fd);
	if (d->alight_count != 1 || d->cam_count != 1 || d->light_count != 1)
		ft_error("Error: Cam, ambiant light and/or light count is invalid\n");
}
