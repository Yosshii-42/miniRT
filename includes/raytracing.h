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

typedef struct s_ray
{
	t_xyz	pos;
	t_xyz	dir;
}	t_ray;

// dist is distance, pos is hit position, norm is nomral vector
typedef struct s_hit_point
{
	double	dist;
	t_xyz	pos;
	t_xyz	norm;
	int		index;
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


int				ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray,
					t_xyz *color);
t_xyz			pls_shade(t_obj *obj, t_lit *lit, double diff_ref,
					double spec_ref);

double			convert_x_to_screen(int x);
double			convert_y_to_screen(int y);
void			set_screen_vector(t_xyz *screen, int x, int y, double fov);

double			hit_sphere(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
double			hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
double			hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
double			hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

double			distance_sphere(double *abcd);
double			dist_cylndr(double *abcd, t_obj *obj, t_ray *ray,
					t_hit_point *h_obj);
double			hit_cylinder_caps(t_obj *obj, t_ray *ray, t_xyz norm_c);
double			get_nearest_inter_cy(t_obj *obj, t_xyz *h_pos, double *t,
					t_xyz norm_c);

void			fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj);
void			set_hit_obj(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					double dist);
void			set_h_obj_cy(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					double *t);

t_xyz			calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec);

int				hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p);
int				hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p);

void			is_light_inside_sp(t_obj *obj, t_lit *lit);
void			is_light_inside_cy(t_obj *obj, t_lit *lit);

int				hit_nearest_obj(t_obj *obj, t_ray *ray,
					t_hit_point *hit_p);
int				hit_shadow_ray(t_obj *obj, t_ray *sh_ray,
					t_hit_point *hit_p);

void			check_light_and_cam_pos(t_obj *obj, t_lit *lit,
					t_ray cam_ray);
void			check_light_pos(t_obj *obj, t_env *env,
					t_ray cam_ray);

unsigned int	clamp(double value, int min, int max);
double			clamp_double(double value, double min, double max);
void			clamp_xyz(t_xyz *rgb, double min, double max);

t_xyz			calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj,
					t_ray cam_ray);

int				calc_shadow(t_obj *obj, t_lit *lit, t_hit_point *hit_p);

int				set_amb_col(t_xyz *color, t_env *env);
void			pls_amb_color(t_obj *obj, t_env *env, t_xyz *col);
t_xyz			pls_shade(t_obj *obj, t_lit *lit, double diff_ref,
					double spec_ref);
void			color_set_to_pixel(t_meta_img *img, int x, int y,
					unsigned int color);

bool			hit_cy_core(t_cy *cy, t_hit_point *hit);
bool			hit_cy_side(t_cy *cy, t_hit_point *hit);
bool			hit_cy_caps(t_cy *cy, t_hit_point *hit);
bool			hit_cy_cap(t_cy *cy, t_xyz center, t_xyz normal, t_hit_point *hit);

#endif
