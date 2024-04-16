#ifndef DATA_H
# define DATA_H

typedef struct s_data
{
	int			fd;
	mlx_image_t	*img;
	t_cam		cam;
	t_shape		shapes;
	t_amb		amb;
	t_lum		lum;
	t_env		env;
	int			cam_count;
	int			light_count;
	int			alight_count;
	char		c1;
	char		c2;
}				t_data;

#endif