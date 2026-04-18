/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:10:58 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/18 23:52:19 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "parser.h"
# include "ui.h"
# include "types.h"
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

// render.c
int				render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env);
int				ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray,
					t_xyz *color);

// render_utils.c
void			reset_light_flags(t_env *env);
void			init_offset(double sx[4], double sy[4]);

// camera.c
t_xyz			calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec);

// screen.c
double			convert_x_to_screen(double x);
double			convert_y_to_screen(double y);
void			set_screen_vector(t_xyz *screen, double x, double y,
					double fov);

// light.c
void			check_light_and_cam_pos(t_obj *obj, t_lit *lit,
					t_ray cam_ray);
void			is_light_inside_cy(t_obj *obj, t_lit *lit);
void			is_light_inside_sp(t_obj *obj, t_lit *lit);
void			check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray);

// shade.c
t_xyz			calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj,
					t_ray cam_ray);
t_xyz			pls_shade(t_data_set data, double diff_ref, double spec_ref);
int				set_amb_col(t_xyz *color, t_env *env);
void			pls_amb_color(t_obj *obj, t_env *env, t_xyz *col,
					t_hit_point hit);

// shadow.c
int				calc_shadow(t_obj *obj, t_lit *lit, t_hit_point *hit_p);

// color.c
unsigned int	clamp(double value, int min, int max);
double			clamp_double(double value, double min, double max);
void			clamp_xyz(t_xyz *rgb, double min, double max);
void			color_set_to_pixel(t_meta_img *img, int x, int y,
					unsigned int color);

// texture.c
t_xyz			get_optional_color(t_obj *obj, t_hit_point hit);
unsigned int	get_tex_pixel(t_meta_img *tex, int x, int y);
t_xyz			color_from_int(unsigned int c);

// texture_pl.c
t_xyz			get_pl_checker_color(t_obj *obj, t_hit_point hit);
t_xyz			get_pl_texture_color(t_obj *obj, t_hit_point hit,
					t_meta_img *tex);

// texture_sp.c
void			get_sp_uv(t_obj *obj, t_hit_point hit, double *u, double *v);
t_xyz			get_sp_checker_color(t_obj *obj, t_hit_point hit);
t_xyz			get_sp_texture_color(t_obj *obj, t_hit_point hit,
					t_meta_img *tex);

// hit.c
double			hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);
int				hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p);
int				hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p);
void			fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj);

// hit_utils.c
void			init_variables(int *ret, int *i, t_obj **obj_cpy, t_obj *obj);
void			init_hit_p(t_hit_point *hit);
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
bool			hit_cy_cap(t_cy *cy, t_xyz normal, t_hit_part part,
					t_hit_point *hit);

// obj_cone.c
double			hit_cone(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

// init.c
void			init_t_hit_point(t_hit_point *tmp);
void			set_init_cylinder_data(t_cy *cy, t_obj *obj, t_ray *ray);
void			set_init_cone_data(t_cn *cn, t_obj *obj, t_ray *ray);

#endif
