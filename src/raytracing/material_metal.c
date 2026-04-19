#include "raytracing.h"
#include "calc.h"

t_xyz	calc_metal(t_scene *scene, t_ray ray, t_hit_point *hit, int depth)
{
	t_ray	ref_ray;
	t_xyz	ref_color;
	t_xyz	dir;
	double	k;

	if (depth == 0)
		return (make_xyz(0, 0, 0));
	dir = refrect(normalize(ray.dir), normalize(hit->norm));
	ref_ray.pos = vec_add(hit->pos, vec_scale(hit->norm, EPSILON));
	ref_ray.dir = normalize(dir);
	ref_color = ray_tracing(scene, ref_ray, depth - 1);
	scene->obj->rgb = make_xyz(255, 200, 50);
	k = 0.2;
	ref_color.x = ref_color.x * (1.0 - k)
		+ ref_color.x * scene->obj->rgb.x / 255.0 * k;
	ref_color.y = ref_color.y * (1.0 - k)
		+ ref_color.y * scene->obj->rgb.y / 255.0 * k;
	ref_color.z = ref_color.z * (1.0 - k)
		+ ref_color.z * scene->obj->rgb.z / 255.0 * k;
	return (ref_color);
}
