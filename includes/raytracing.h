/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:10:58 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/30 23:41:52 by yosshii          ###   ########.fr       */
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

# define M_PI 3.14159265358979323846
# define RENDERED_SHADOW 0
# define NOT_RENDERED_SHADOW 1
# define NO_LIGHT 2

// raytracing.c
// int				render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env);
t_xyz			ray_tracing(t_scene *scene, t_ray cam_ray, int depth);

// raytracing_utils.c
void			reset_light_flags(t_env *env);
void			init_offset(double sx[4], double sy[4]);
t_shade_ctx		set_shade_data(t_obj *obj, t_hit_point hit, t_ray ray);
t_obj			get_indexed_obj(int index, t_obj *obj);

// camera.c
t_xyz			calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec);

// screen.c
void			set_screen_vector(t_xyz *screen, double x, double y,
					double fov);

// light.c
void			check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray);

// shade.c
t_xyz			calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj,
					t_ray cam_ray);
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

// obj_plane.c
double			hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

// obj_cylinder.c
double			hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

// obj_cylinder_core.c
bool			hit_cy_side(t_cy *cy, t_hit_point *hit);
bool			hit_cy_caps(t_cy *cy, t_hit_point *hit);
bool			hit_cy_cap(t_cy *cy, t_xyz normal, t_hit_part part,
					t_hit_point *hit);

// obj_cone.c
double			hit_cone(t_obj *obj, t_ray *ray, t_hit_point *h_obj,
					bool rec_hit);

// material_metal.c
t_xyz			calc_metal(t_scene *scene, t_ray ray, t_hit_point *hit,
					int depth);

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

// bump.c
t_xyz			apply_bump(t_hit_point *hit);
t_xyz			apply_bump_sp(t_obj *obj, t_hit_point hit);

// init.c
void			init_t_hit_point(t_hit_point *tmp);
void			set_init_cylinder_data(t_cy *cy, t_obj *obj, t_ray *ray);
void			set_init_cone_data(t_cn *cn, t_obj *obj, t_ray *ray);
t_scene			set_scene_data(t_env *env, t_obj *obj);

#endif
