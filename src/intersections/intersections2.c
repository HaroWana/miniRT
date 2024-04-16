#include "miniRT.h"

void	inter_eq(t_inter *inter1, t_inter *inter2)
{
	*inter1 = inter_cpy_ray(&inter2->ray);
	inter1->t = inter2->t;
	inter1->rgb = inter2->rgb;
}
