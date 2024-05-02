#include "miniRT.h"

t_data	d;

static void	d_init(int width, int height)
{
	d.env.width = width;
	d.env.height = height;
	d.env.mlx = mlx_init(d.env.width, d.env.height, "miniRT", true);
	d.img = mlx_new_image(d.env.mlx, d.env.width, d.env.height);

	d.imgData = calloc(height + 1, sizeof(uint32_t *));
	for (int i = 0; i < height; i++)
		d.imgData[i] = calloc(width + 1, sizeof(uint32_t));
	if (!d.imgData)
		ft_error(0, "Image init failure\n");

	d.shapes.cylindres = NULL;
	d.shapes.spheres = NULL;
	d.shapes.planes = NULL;
	d.cam_count = 0;
	d.light_count = 0;
	d.alight_count = 0;
}

static void	save_to_img(char *filename)
{
	printf("Saving image as PPM file...\n");
	int	fd = open(filename, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0644);
	char *ppm = canvas_to_ppm();
	ft_putstr_fd(ppm, fd);
	free(ppm);
	close(fd);
	printf("Success!\n");
}

int	main(int ac, char **av)
{
	if (ac != 2 && ac != 4)
	{
		printf("usage: ./miniRT scene_file [-S filename]\n  options:\n    -S filename	- Save your scene in ppm format\n");
		return(0);
	}

	d_init(600, 400);
	load_data(av[1]);
	ray_trace(&d);

	if (ac == 4 && ft_strncmp(av[2], "-S", 2) == 0)
		save_to_img(av[3]); 
	
	mlx_loops(&d);

	clean_up();
	return (0);
}
