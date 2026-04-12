#include "raytracing.h"
#include "calc.h"

void	set_face_normal(t_ray *ray, t_hit_point *h_obj)
{
	if (dot(ray->dir, h_obj->norm) > 0)
		h_obj->norm = multi_v_f(h_obj->norm, -1.0);
}