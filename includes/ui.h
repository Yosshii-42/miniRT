
#ifndef UI_H
# define UI_H

#include "./parser.h"

# define W_WIDTH 800
# define W_HEIGHT 450
# define WIN_TITLE "minirt"
# define DESTROY_NOTIFY 17


typedef struct s_meta_img
{
	void	*img;
	char	*addr;
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

int	close_btn_click(t_mlx_env *mlx);
int	init_window(t_obj *data, t_env *env);
int	render_window(t_mlx_env *mlx, t_obj *obj, t_env *env);
int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env);
double	hit_ray(t_obj *obj, t_env *env, t_xyz cam_dir);

#endif