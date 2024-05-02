#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_data	t_data;

void	save_img(mlx_image_t *img, char *filename);

void	ray_trace(t_data *d);

char	*canvas_to_ppm();

#endif