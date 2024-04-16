#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_cam
{
	t_vec		pos;
	t_vec		forward;
	t_vec		up;
	t_vec		right;
	float		h;
	float		w;
	float		fov;
}				t_cam;

void	cam_init(t_cam *c, float aspect_ratio);

t_ray	make_ray(t_cam *c, t_vec2 point);

#endif
