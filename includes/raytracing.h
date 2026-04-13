/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:10:58 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/23 21:05:16 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "./parser.h"
# include "./ui.h"
# define SHINENESS 16
# define NO_HIT -99
# define MAX_DIST 65535
# define EPS 0.000001f
# define EPSILON 0.0078125f
# define PLANE_PARALLEL 1e-6
# define M_PI 3.14159265358979323846
# define RENDERED_SHADOW 0
# define NOT_RENDERED_SHADOW 1
# define NO_LIGHT 2

typedef enum e_letter
{
	L_A,
	L_B,
	L_C,
	L_D
}	t_letter;

typedef enum e_hit_part
{
	HIT_NONE,
	HIT_CY_SIDE,
	HIT_CY_CAP_TOP,
	HIT_CY_CAP_BOTTOM,
	
	HIT_SPHERE,
	hIT_PLANE
}	t_hit_part;

typedef struct s_ray
{
	t_xyz	pos;
	t_xyz	dir;
}	t_ray;

// dist is distance, pos is hit position, norm is nomral vector
typedef struct s_hit_point
{
	double		dist;
	t_xyz		pos;
	t_xyz		norm;
	int			index;
	t_hit_part	part;
}	t_hit_point;

typedef struct s_cy
{
	t_ray	ray;
	t_obj	*obj;
	t_xyz	axis;
	double	radius;
	double	half_h;
	double	min;
	double	max;
}	t_cy;

// render.c
int				ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color);

// camera.c
t_xyz			calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec);

// screen.c
double			convert_x_to_screen(int x);
double			convert_y_to_screen(int y);
void			set_screen_vector(t_xyz *screen, int x, int y, double fov);

// light.c
void			check_light_and_cam_pos(t_obj *obj, t_lit *lit, t_ray cam_ray);
void			is_light_inside_cy(t_obj *obj, t_lit *lit);
void			is_light_inside_sp(t_obj *obj, t_lit *lit);
void			check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray);

// shade.c
t_xyz			calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj,
					t_ray cam_ray);
t_xyz			pls_shade(t_obj *obj, t_lit *lit, double diff_ref,
					double spec_ref);					
int				set_amb_col(t_xyz *color, t_env *env);
void			pls_amb_color(t_obj *obj, t_env *env, t_xyz *col);

// shadow.c
int				calc_shadow(t_obj *obj, t_lit *lit, t_hit_point *hit_p);

// color.c
unsigned int	clamp(double value, int min, int max);
double			clamp_double(double value, double min, double max);
void			clamp_xyz(t_xyz *rgb, double min, double max);
void			color_set_to_pixel(t_meta_img *img, int x, int y,
					unsigned int color);

// hit.c
double			hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
int				hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p);
int				hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p);
void			fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj);
void			set_face_normal(t_ray *ray, t_hit_point *h_obj);

// obj_shpere.c
double			hit_sphere(t_obj *obj, t_ray *ray);
double			distance_sphere(double *abcd);

// obj_plane.c
double			hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

// obj_cylinder.c
double			hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
bool			hit_cy_core(t_cy *cy, t_hit_point *hit);

// obj_cylinder_core.c
bool			hit_cy_side(t_cy *cy, t_hit_point *hit);
bool			hit_cy_caps(t_cy *cy, t_hit_point *hit);
bool			hit_cy_cap(t_cy *cy, t_xyz center, t_xyz normal, t_hit_part part,
					t_hit_point *hit);
bool			judge_t(t_cy *cy, t_hit_point *hit, double t);
void			calc_cy_side_abc(t_cy *cy, double abc[3]);

// unused
void			set_hit_obj(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					double dist);

#endif
