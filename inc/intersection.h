#ifndef INTERSECTION_H
# define INTERSECTION_H

typedef struct s_inter
{
	t_ray		ray;
	t_vec		normal;
	t_vec		pos;
	float		t;
	int			rgb;
}				t_inter;

t_inter	inter_init(void);
t_inter	inter_cpy_ray(t_ray *ray1);
void	inter_eq(t_inter *inter1, t_inter *inter2);

#endif