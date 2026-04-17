#include "raytracing.h"
#include "calc.h"

void	init_t_hit_point(t_hit_point *tmp)
{
	tmp->dist = MAX_DIST;
	tmp->index = -1;
	init_xyz(&tmp->pos);
	init_xyz(&tmp->norm);
}

void	set_init_cone_data(t_cn *cn, t_obj *obj, t_ray *ray)
{
	cn->ray = *ray;
	cn->obj = obj;
	cn->axis = normalize(obj->vector);
	cn->radius = obj->diameter / 2.0;
	cn->height = obj->height;
	cn->co = vec_sub(ray->pos, obj->xyz);
	cn->k = sqr(cn->radius / cn->height);
	cn->dir_axis = dot(ray->dir, cn->axis);
	cn->co_axis = dot(cn->co, cn->axis);
}
