#include "miniRT.h"

extern t_data	d;

static void	load_line(char *buf)
{
	char	**split;
	int		ret = 1;
	split = ft_split_words(buf);

	if (ft_strncmp(split[0], "A", 1) == 0 && ft_strlen(split[0]) == 1)
		ret = amb(split);
	else if (ft_strncmp(split[0], "C", 1) == 0 && ft_strlen(split[0]) == 1)
		ret = cam(split);
	else if (ft_strncmp(split[0], "L", 1) == 0 && ft_strlen(split[0]) == 1)
		ret = lum(split);
	else if (ft_strncmp(split[0], "sp", 2) == 0 && ft_strlen(split[0]) == 2)
		ret = sp(split);
	else if (ft_strncmp(split[0], "pl", 2) == 0 && ft_strlen(split[0]) == 2)
		ret = pl(split);
	else if (ft_strncmp(split[0], "cy", 2) == 0 && ft_strlen(split[0]) == 2)
		ret = cyl(split);
	
	ft_arr_freer(split);
	if (ret)
	{
		close(d.fd);
		ft_error(ret, buf);
	}
}

void	load_data(char *filename)
{
	char	*buf;

	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3) != 0)
		ft_error(0, "This program requires a .rt scene file.");
	d.fd = open(filename, O_RDONLY);
	if (d.fd < 0)
	{
		close(d.fd);
		ft_error(0, "Invalid file");
	}
	buf = get_next_line(d.fd);
	if (!buf)
		ft_error(0, "File is empty");
	while (buf)
	{
		if (*buf != '\n' && *buf != '\r')
			load_line(buf);
		free(buf);
		buf = NULL;
		buf = get_next_line(d.fd);
	}
	close(d.fd);
	if (d.alight_count != 1 || d.cam_count != 1 || d.light_count != 1)
		ft_error(0, "Cam, ambiant light and/or light count is invalid");
}
