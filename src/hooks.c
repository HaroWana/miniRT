#include "miniRT.h"
// d handling is to be reworked globally
void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		clean_up();
		close_hook(d, 0);
	}
}

void	expose_img(t_data *d)
{
	if (mlx_image_to_window(d->env.mlx, d->img, 0, 0) < 0)
	{
		mlx_close_window(d->env.mlx);
		ft_error("Error\nimpossible to create image\n");
	}
}

// static void	resize_hook(int width, int height, void *param)
// {
// 	t_data	*d;

// 	d = (t_data *)param;
// 	if (width < 0 || height < 0)
// 	{
// 		mlx_close_window(d->env.mlx);
// 		ft_error("Error\nimpossible to resize window\n");
// 	}
// 	mlx_resize_image(d->img, width, height);
// 	ray_trace(d);
// }

void	mlx_loops(t_data *d)
{
	mlx_key_hook(d->env.mlx, &keyhook, &d->env);
	mlx_loop(d->env.mlx);
}
