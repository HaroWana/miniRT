#include "miniRT.h"

t_data	d;

static void	d_init(int width, int height)
{
	d.env.width = width;
	d.env.height = height;
	d.env.mlx = mlx_init(d.env.width, d.env.height, "miniRT", true);
	d.img = mlx_new_image(d.env.mlx, d.env.width, d.env.height);
	d.img_data = malloc(sizeof(unsigned int *) * height + 1);
	if (!d.img_data)
		ft_error(0, "Image init failure\n");
	ft_bzero(d.img_data, sizeof(unsigned int *) * height + 1);
	for (int i = 0; i < height; i++)
		d.img_data[i] = malloc(sizeof(unsigned int) * width + 1);
	
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
	int	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
	char *ppm = canvas_to_ppm();
	ft_putstr_fd(ppm, fd);
	free(ppm);
	close(fd);
	printf("Success!\n");
	clean_up();
}



int	main(int ac, char **av)
{
	(void)ac;
	// GLuint texid;

	// raytracer init
	d_init(400, 300);
	load_data(av[1]);
    ray_trace();

	if (av[2] && av[3] && ft_strncmp(av[2], "-S", 2) == 0)
	{
		save_to_img(av[3]);
	}
	mlx_loops(&d);

	clean_up();
	return (0);
}
