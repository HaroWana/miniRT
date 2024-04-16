#ifndef SHAPE_H
# define SHAPE_H

typedef struct s_elem
{
	t_vec			pos;
	t_vec			axe;
	t_vec			normal;
	float			radius;
	float			height;
	int				rgb;
	struct s_elem	*next;
}				t_elem;

typedef struct s_shape
{
	int		sphere_nb;
	int		plane_nb;
	int		cyl_nb;
	t_elem	*spheres;
	t_elem	*planes;
	t_elem	*cylindres;

}				t_shape;

bool	shapes_intersect(t_shape *shapes, t_inter *inter);

#endif