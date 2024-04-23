#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <stdint.h>

# include "vector.h"
# include "ray.h"
# include "intersection.h"
# include "shape.h"
# include "camera.h"
# include "env.h"
# include "light.h"
# include "data.h"
# include "image.h"

// main.c
int		main(int ac, char **av);
void	ft_error(char *str);
void	keyhook(mlx_key_data_t keydata, void *param);

// check.c
int		rgbinrange(int nb);
void	vectinrange(t_data *d, char **str);
int		ratioinrange(char *ratio);
int		fovinrange(int nb);
void	check_pos(t_data *d, char **pos);
void	check_radius(t_data *d, char *radius);
int		split_count(char **split);

// init.c
void	init_rt(t_env e, t_data d);

// load.c
void	load_data(t_data *d, char *filename);

// amb.c
void	amb(char **split, t_data *d);

// cam.c
void	cam(char **split, t_data *d);

// lum.c
void	lum(char **split, t_data *d);

// spher.c
void	sp(char **split, t_data *d);

// plan.c
void	pl(char **split, t_data *d);

// cyl.c
void	cyl(char **split, t_data *d);

// cmpt.c
void	free_all(char **tmp, char **tmp_pos, char **tmp_axe, char **tmpcolor);

// utils.c
bool	ft_isint(char *str);
bool	ft_isrgb(int color);
float	sqr(float f);
bool	ft_isfloat(const char *str);
void	shapes_addback(t_elem **lst, t_elem *new, int *qty);
t_elem	*elem_init(void);
t_vec	get_coor(char **split);

// utils2.c

float	sqr(float f);
int		get_color(char **split);

// ft_split_words.c

char	**ft_split_words(char const *s);

// exit.c
int		close_hook(t_data *d, int code);

// hooks.c
void	keyhook(mlx_key_data_t keydata, void *param);
void	expose_img(t_data *d);
void	mlx_loops(t_data *d);

// New color functions -> will eventually replace color.c and color2.c

int		get_color(char **split);
int		color_scale(int colour, float f);
int		color_prod(int c1, int c2);
int		color_add(int c1, int c2);
int		color_comp(t_lum *light, t_inter hit);

bool	hit_sp(t_inter *inter, t_elem *elem);
bool	hit_cy(t_inter *inter, t_elem *elem);
bool	hit_pl(t_inter *inter, t_elem *elem);

#endif
