#include "calc.h"

double	vec_length_sq(t_xyz v)
{
	return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double	vec_length(t_xyz v)
{
	return (sqrt(vec_length_sq(v)));
}

double	vec_dist(t_xyz a, t_xyz b)
{
	t_xyz	diff;

	diff = vec_sub(a, b);
	return (sqrt(vec_length_sq(diff)));
}
