#ifndef INTERSECTION_H
# define INTERSECTION_H

typedef struct s_cyl	t_cyl;
typedef struct s_inter
{
	t_ray		ray;
	t_vec		normal;
	t_vec		pos;
	float		t;
	int			rgb;
}				t_inter;

//-----Instanciation-----//
t_inter	inter_init(void);
t_inter	inter_cpy(t_inter *inter1);
t_inter	inter_cpy_ray(t_ray *ray1);

//-----Manipulations-----//
bool	intersected(t_inter *inter1);
t_vec	inter_position(t_inter *inter1);

//-----Operations-----//
void	inter_eq(t_inter *inter1, t_inter *inter2);

#endif