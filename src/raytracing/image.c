#include "raytracing.h"
#include "calc.h"

unsigned int	get_tex_pixel(t_meta_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_xyz	color_from_int(unsigned int c)
{
	return (make_xyz((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF));
}

t_xyz	get_sp_texture_color(t_obj *obj, t_hit_point hit, t_meta_img *tex)
{
	double			u;
	double			v;
	int				px;
	int				py;
	unsigned int	c;

	get_sphere_uv(obj, hit, &u, &v);
	px = (int)(u * (tex->width - 1));
	py = (int)(v * (tex->height - 1));
	c = get_tex_pixel(tex, px, py);
	return (color_from_int(c));
}
