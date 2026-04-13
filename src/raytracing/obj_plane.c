#include "calc.h"
#include "parser.h"
#include "raytracing.h"

//ray : →p = →s + t→d
//plane: (→p・→n)= 0
// t = - (→s・→n) / (→d・→n) t> 0 のとき交点を持つ
double	hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_xyz	p_norm;
	double	numerator;
	double	denominator;
	double	ret;

	(void)h_obj;
	(void)rec_hit;
	p_norm = normalize(obj->vector);
	denominator = dot(ray->dir, p_norm);
	if (fabs(denominator) < PLANE_PARALLEL)
		return (NO_HIT);
	numerator = dot(vec_sub(obj->xyz, ray->pos), p_norm);
	ret = numerator / denominator;
	if (ret <= EPSILON)
		return (NO_HIT);
	return (ret);
}