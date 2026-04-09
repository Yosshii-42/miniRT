#include "calc.h"
#include "raytracing.h"

bool	solve_quadratic(double abc[3], double *t0, double *t1)
{
	double	d;
	double	tmp;

	if (fabs(abc[0]) < EPS)
		return (false);
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0.0)
		return (false);
	d = sqrt(d);
	*t0 = (-abc[1] - d) / (2.0 * abc[0]);
	*t1 = (-abc[1] + d) / (2.0 * abc[0]);
	if (*t1 < *t0)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
	return (true); 
}
