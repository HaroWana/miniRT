#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_amb
{
	int			nb_a;
	float		ratio;
	int			rgb;
}				t_amb;

typedef struct s_lum
{
	int			nb_l;
	t_vec		pos;
	float		ratio;
	int			rgb;
}				t_lum;

#endif