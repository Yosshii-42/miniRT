
#include "calc.h"
#include "parser.h"
#include "raytracing.h"

// 軸を正規化
// top/bottom centerを作る
//　side
// cap
// cap
// 一番近いものを採用
double	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_cy		cy;
	t_hit_point	tmp;

	cy.ray = *ray;
	cy.obj = obj;
	cy.axis = normalize(obj->vector);
	cy.radius = obj->diameter / 2.0;
	cy.half_h = obj->height / 2.0;
	cy.min = EPS;
	cy.max = MAX_DIST;
	if (!hit_cy_core(&cy, &tmp))
		return (NO_HIT);
	if (rec_hit)
	{
		*h_obj = tmp;
		set_face_normal(ray, h_obj);
	}
	return (tmp.dist);
}


/*
** hit_cy_core
** 円柱全体（側面 + キャップ）の交差判定
** 1. 側面との交差をチェック
**    → ヒットしたら最短距離を max に更新
** 2. キャップ（上面・下面）との交差をチェック
**    → 側面より近いものがあれば上書き
** 3. 最終的に最も近い交点を hit に格納
** ※ cy->max を更新することで「一番近いもの」を維持している
*/
bool	hit_cy_core(t_cy *cy, t_hit_point *hit)
{
	t_hit_point	side_hit;
	t_hit_point	cap_hit;
	bool		has_side;
	bool		has_cap;

	has_side = hit_cy_side(cy, &side_hit);
	has_cap = hit_cy_caps(cy, &cap_hit);
	if (!has_side && !has_cap)
		return (false);
	if (has_side && !has_cap)
		return (*hit = side_hit, true);
	if (!has_side && has_cap)
		return (*hit = cap_hit, true);
	if (side_hit.dist < cap_hit.dist)
		*hit = side_hit;
	else
		*hit = cap_hit;
	return (true);
}
