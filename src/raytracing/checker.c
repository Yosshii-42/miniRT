#include "parser.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

t_xyz	get_checker_color(t_obj *obj, t_hit_point hit)
{
	int		check;
	int		ix;
	int		iz;
	double	scale;
	t_env	*env;

	env = set_get_env(GET, NULL);
	if (obj->id == PL && (obj->vector.y == 1 || obj->vector.y == -1))
	{
		scale = 0.2;
		ix = (int)floor(hit.pos.x * scale);
		iz = (int)floor(hit.pos.z * scale);
		check = (ix + iz) & 1;
		if (check == 0)
			return (make_xyz(255, 255, 255));
		return (make_xyz(0.0, 0.0, 0.0));
	}
	if (obj->id == SP)
		return (get_sp_texture_color(obj, hit, &(env->tex)));
		// return (get_sp_checker_color(obj, hit));
	return (obj->rgb);
}

// p は球の表面上の位置を、中心基準で表す
// atan2(p.z, p.x) で横方向
// asin(p.y) で縦方向
void	get_sphere_uv(t_obj *obj, t_hit_point hit, double *u, double *v)
{
	t_xyz	p;

	p = vec_sub(hit.pos, obj->xyz);
	p = normalize(p);
	*u = atan2(p.z, p.x) / (2.0 * M_PI) + 0.5;
	*v = 0.5 - asin(p.y) / M_PI;
}

t_xyz	get_sp_checker_color(t_obj *obj, t_hit_point hit)
{
	double	u;
	double	v;
	int		iu;
	int		iv;
	double	scale;

	get_sphere_uv(obj, hit, &u, &v);
	scale = 20.0;
	iu = (int)floor(u * scale);
	iv = (int)floor(v * scale);
	if (((iu + iv) & 1) == 0)
		return (make_xyz(255.0, 255.0, 255.0));
	return (make_xyz(0.0, 0.0, 0.0));
}
