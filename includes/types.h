/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:19:36 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/20 16:11:16 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define EPS 0.000001f
# define EPSILON 0.0078125f

enum
{
	A,
	C,
	L,
	PL,
	SP,
	CY,
	CN,
	IM,
	CH,
};

typedef enum e_material
{
	DEFAULT,
	METAL
}	t_material;

typedef struct s_meta_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_meta_img;

typedef struct s_mlx_env
{
	void		*mlx;
	void		*window;
	t_meta_img	*img;
}	t_mlx_env;

typedef struct s_xyx
{
	double	x;
	double	y;
	double	z;
}	t_xyz;

typedef struct s_lit
{
	int				flag;
	t_xyz			xyz;
	double			t;
	t_xyz			rgb;
	bool			valid_flag;
	struct s_lit	*next;
}	t_lit;

typedef struct s_env
{
	int			part;
	int			flag[3];
	double		amb_t;
	t_xyz		amb_rgb;
	t_xyz		cam_xyz;
	t_xyz		cam_vector;
	double		cam_degree;
	t_lit		*lit;
}	t_env;

typedef struct s_obj
{
	int				id;
	t_material		material;
	t_xyz			xyz;
	t_xyz			vector;
	t_xyz			rgb;
	double			diameter;
	double			height;
	int				texture;
	char			*filename;			
	struct s_obj	*next;
	t_meta_img		tex;
}	t_obj;

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
	t_xyz	top;
	t_xyz	bottom;
	t_xyz	oc;
	double	a;
	double	b;
	double	c;
}	t_cy;

typedef struct s_cn
{
	t_ray	ray;
	t_obj	*obj;
	t_xyz	axis;
	double	radius;
	double	height;
	t_xyz	co;
	double	k;
	double	dir_axis;
	double	co_axis;
	double	a;
	double	b;
	double	c;
}	t_cn;

typedef struct s_data_set
{
	t_obj		*obj;
	t_lit		*lit;
	t_hit_point	hit_p;
}	t_data_set;

typedef struct s_scene
{
	t_env	*env;
	t_lit	*lit;
	t_obj	*obj;
}	t_scene;

typedef struct s_shade_ctx
{
	t_obj		*obj;
	t_hit_point	hit;
	t_ray		ray;
}	t_shade_ctx;

#endif
