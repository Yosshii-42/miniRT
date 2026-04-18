#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

void	reset_light_flags(t_env *env)
{
	t_lit	*l;

	l = env->lit;
	while (l)
	{
		l->valid_flag = true;
		l = l->next;
	}
}

void	init_offset(double sx[4], double sy[4])
{
	sx[0] = 0.25;
	sx[1] = 0.75;
	sx[2] = 0.25;
	sx[3] = 0.75;
	sy[0] = 0.25;
	sy[1] = 0.25;
	sy[2] = 0.75;
	sy[3] = 0.75;
}
