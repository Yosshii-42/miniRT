#include "calc.h"
#include "parser.h"
#include "raytracing.h"

static void	set_cone_normal(t_cn *cn, t_hit_point *hit)
{
	t_xyz	cp;
	double	proj;

	cp = vec_sub(hit->pos, cn->obj->xyz);
	proj = dot(cp, cn->axis);
	hit->norm = vec_sub(cp, vec_scale(cn->axis, (1.0 + cn->k) * proj));
	hit->norm = normalize(hit->norm);
}

static bool	judge_cone_t(t_cn *cn, t_hit_point *hit, double t)
{
	t_xyz	position;
	double	m;

	position = vec_add(cn->ray.pos, vec_scale(cn->ray.dir, t));
	m = dot(vec_sub(position, cn->obj->xyz), cn->axis);
	if (-cn->height <= m && m <= 0.0)
	{
		hit->dist = t;
		hit->pos = position;
		return (true);
	}
	return (false);
}

static bool	hit_cone_side(t_cn *cn, t_hit_point *hit)
{
	double	t0;
	double	t1;
	double	discriminant;

	cn->a = dot(cn->ray.dir, cn->ray.dir) - (1.0 + cn->k) * sqr(cn->dir_axis);
	if (fabs(cn->a) < EPS)
		return (false);
	cn->b = 2.0 * (dot(cn->ray.dir, cn->co)
			- (1.0 + cn->k) * cn->dir_axis * cn->co_axis);
	cn->c = dot(cn->co, cn->co) - (1.0 + cn->k) * sqr(cn->co_axis);
	discriminant = sqr(cn->b) - 4.0 * cn->a * cn->c;
	if (discriminant < 0)
		return (false);
	t0 = (-cn->b - sqrt(discriminant)) / (2.0 * cn->a);
	t1 = (-cn->b + sqrt(discriminant)) / (2.0 * cn->a);
	if (t0 > EPSILON && judge_cone_t(cn, hit, t0))
		return (true);
	if (t1 > EPSILON && judge_cone_t(cn, hit, t1))
		return (true);
	return (false);
}

static bool	hit_cone_cap(t_cn *cn, t_hit_point *hit)
{
	t_xyz	base_center;
	t_xyz	position;
	t_xyz	direction;
	double	t;

	base_center = vec_sub(cn->obj->xyz, vec_scale(cn->axis, cn->height));
	if (fabs(cn->dir_axis) < EPS)
		return (false);
	t = dot(vec_sub(base_center, cn->ray.pos), cn->axis) / cn->dir_axis;
	if (t <= EPSILON)
		return (false);
	position = vec_add(cn->ray.pos, vec_scale(cn->ray.dir, t));
	direction = vec_sub(position, base_center);
	if (dot(direction, direction) > sqr(cn->radius))
		return (false);
	hit->dist = t;
	hit->pos = position;
	hit->norm = vec_scale(cn->axis, -1.0);
	return (true);
}

double	hit_cone(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_cn		cn;
	t_hit_point	side_hit;
	t_hit_point	cap_hit;
	bool		has_side;
	bool		has_cap;

	set_init_cone_data(&cn, obj, ray);
	init_t_hit_point(&side_hit);
	init_t_hit_point(&cap_hit);
	has_side = hit_cone_side(&cn, &side_hit);
	has_cap = hit_cone_cap(&cn, &cap_hit);
	if (!has_side && !has_cap)
		return (NO_HIT);
	if (has_side && (!has_cap || side_hit.dist < cap_hit.dist))
	{
		*h_obj = side_hit;
		if (rec_hit)
			set_cone_normal(&cn, h_obj);
	}
	else
		*h_obj = cap_hit;
	if (rec_hit)
		set_face_normal(ray, h_obj);
	return (h_obj->dist);
}
