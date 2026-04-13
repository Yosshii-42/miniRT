/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_camera_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:26:32 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:27:07 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

t_xyz	calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec)
{
	t_xyz	dir;
	t_xyz	forward;
	t_xyz	up;
	t_xyz	right;

	forward = normalize(cam_vec);
	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (fabs(dot(forward, up)) > 0.999)
		up = (t_xyz){1, 0, 0};
	right = normalize(cross(up, forward));
	up = cross(forward, right);
	dir = normalize(\
		vec_add(\
			vec_add(\
				vec_scale(right, screen_vec.x), vec_scale(up, screen_vec.y)), \
				forward));
	return (dir);
}
