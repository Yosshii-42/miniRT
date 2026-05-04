#include "raytracing.h"
#include "calc.h"

static double	rand01(void)
{
	return ((double)rand() / (double)RAND_MAX);
}

static t_xyz	random_in_unit_sp(void)
{
	t_xyz	p;

	while (1)
	{
		p = make_xyz(rand01() * 2.0 - 1.0,
				rand01() * 2.0 - 1.0,
				rand01() * 2.0 - 1.0);
		if (vec_length_sq(p) < 1.0)
			return (p);
	}
}

t_xyz	calc_ref_color(t_xyz ref_color, t_xyz metal_col)
{
	double	k;
	t_xyz	result_col;

	k = 0.2;
	init_xyz(&result_col);
	result_col.x = ref_color.x * (1.0 - k)
		+ ref_color.x * metal_col.x / 255.0 * k;
	result_col.y = ref_color.y * (1.0 - k)
		+ ref_color.y * metal_col.y / 255.0 * k;
	result_col.z = ref_color.z * (1.0 - k)
		+ ref_color.z * metal_col.z / 255.0 * k;
	return (result_col);
}

t_xyz	calc_metal(t_scene *scene, t_ray ray, t_hit_point *hit, int depth)
{
	t_ray	ref_ray;
	t_xyz	ref_color;
	t_xyz	dir;
	t_xyz	metal_col;
	t_rough	rough;

	if (depth <= 0)
		return (make_xyz(0, 0, 0));
	dir = reflect(normalize(ray.dir), normalize(hit->norm));
	ref_ray.pos = vec_add(hit->pos, vec_scale(hit->norm, EPSILON));
	rough.rand_dir = random_in_unit_sp();
	rough.rand_dir = vec_scale(rough.rand_dir, 0.5);
	if (dot(rough.rand_dir, hit->norm) < 0)
		rough.rand_dir = vec_scale(rough.rand_dir, -1);
	rough.roughness = 0.005;
	ref_ray.dir = normalize(vec_add(dir,
				vec_scale(rough.rand_dir, rough.roughness)));
	ref_color = ray_tracing(scene, ref_ray, depth - 1);
	metal_col = make_xyz(255, 200, 50);
	return (calc_ref_color(ref_color, metal_col));
}
