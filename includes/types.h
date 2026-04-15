#ifndef TYPES_H
# define TYPES_H

enum
{
	A,
	C,
	L,
	PL,
	SP,
	CY
};

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
	t_meta_img	tex;
}	t_env;

typedef struct s_obj
{
	int				id;
	t_xyz			xyz;
	t_xyz			vector;
	t_xyz			rgb;
	double			diameter;
	double			height;
	struct s_obj	*next;
}	t_obj;

#endif
