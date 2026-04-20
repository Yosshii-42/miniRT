/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:25:27 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/20 22:55:34 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "calc.h"

void	open_file(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd == -1)
		print_error_and_exit("open_file", "couldn't open file");
}

void	*safe_malloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = ft_calloc(size, count);
	if (!tmp)
		exit((ft_printf(2, "malloc: %s\n", strerror(errno)), EXIT_FAILURE));
	return (tmp);
}

unsigned int	make_trgb(double t, double r, double g, double b)
{
	t = round(255 * t);
	r = round(r);
	g = round(g);
	b = round(b);
	return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

void	normalize_check(t_xyz vec, char *func_name)
{
	double	len;

	len = vec_length(vec);
	if (fabs(1.0 - len) > EPSILON)
		print_error_and_exit(func_name, "normalized vector required");
}

void	obj_normalize_check(t_obj *obj, char *str)
{
	double	len;

	len = vec_length(obj->vector);
	if (fabs(1.0 - len) > EPSILON)
		print_error_and_exit(str, "normalized vector required");
}
