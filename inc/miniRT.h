#ifndef MINIRT_H
# define MINIRT_H

# define STDERR 2

# include <GLFW/glfw3.h>
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
void	ft_error(int ret, char *str);

// check.c
bool	rgbinrange(int nb);
bool	vectinrange(char **str);
bool	ratioinrange(char *ratio);
bool	fovinrange(int nb);
bool	valid_pos(char **pos);
bool	valid_radius(char *radius);
bool	valid_rgb(char **rgb);
int		split_count(char **split);

// init.c
void	init_rt(t_env e, t_data d);

// load.c
void	load_data(char *filename);

// amb.c
int	amb(char **split);

// cam.c
int	cam(char **split);

// lum.c
int	lum(char **split);

// spher.c
int	sp(char **split);

// plan.c
int	pl(char **split);

// cyl.c
int	cyl(char **split);

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
void	clean_up();


// hooks.c
// void	keyhook(mlx_key_data_t keydata, void *param);
// void	expose_img(t_data *d);
// void	mlx_loops(t_data *d);

int		get_color(char **split);
int		color_scale(int colour, float f);
int		color_prod(int c1, int c2);
int		color_add(int c1, int c2);
int		color_comp(t_lum *light, t_inter hit);

bool	hit_sp(t_inter *inter, t_elem *elem);
bool	hit_cy(t_inter *inter, t_elem *elem);
bool	hit_pl(t_inter *inter, t_elem *elem);

#endif
