#ifndef MINIRT_H
# define MINIRT_H

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
#include <bsd/string.h>
# include <errno.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/types.h>
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

/* Cool little trick to easily print binary */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
	((byte) & 0x80 ? '1' : '0'), \
	((byte) & 0x40 ? '1' : '0'), \
	((byte) & 0x20 ? '1' : '0'), \
	((byte) & 0x10 ? '1' : '0'), \
	((byte) & 0x08 ? '1' : '0'), \
	((byte) & 0x04 ? '1' : '0'), \
	((byte) & 0x02 ? '1' : '0'), \
	((byte) & 0x01 ? '1' : '0')

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

// utils.c
bool	ft_isint(char *str);
bool	ft_isrgb(int color);
int		ft_isdigit(int c);
float	sqr(float f);
bool	ft_isfloat(const char *str);
void	shapes_addback(t_elem **lst, t_elem *new, int *qty);
t_elem	*elem_init(void);
t_vec	get_coor(char **split);
int		numDigits(int num);
char	**ft_split(char const *s, char c);
float	sqr(float f);
int		get_color(char **split);
void	ft_putstr_fd(char *s, int fd);
double	ft_atof(const char *str);
char	*get_next_line(int fd);

// split_words.c
char	**split_words(char const *s);

// exit.c
void	clean_up();
void	free_2D_arr(char **arr);
void	free_2D_arrs(char **tmp, char **tmp_pos, char **tmp_axe, char **tmpcolor);


int		get_color(char **split);
int		color_scale(int colour, float f);
int		color_prod(int c1, int c2);
int		color_add(int c1, int c2);
int		color_comp(t_lum *light, t_inter hit);

bool	hit_sp(t_inter *inter, t_elem *elem);
bool	hit_cy(t_inter *inter, t_elem *elem);
bool	hit_pl(t_inter *inter, t_elem *elem);

#endif
