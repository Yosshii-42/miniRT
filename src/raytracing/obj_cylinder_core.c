#include "calc.h"
#include "parser.h"
#include "raytracing.h"

/*
** hit_cy_side
**
** 円柱側面とレイの交差判定
** 1. 無限円柱との交差を二次方程式で求める
**    → a t² + b t + c = 0
** 2. 解の公式で t0, t1 を求める
** 3. min <= t <= max を満たす解を選び
**    judge_t()で側面法線が得られたらtrueを返す
*/
bool	hit_cy_side(t_cy *cy, t_hit_point *hit)
{
	double abc[3];
    double t0;
	double t1;
    bool found;
    t_hit_point tmp;

	found = false;
    calc_cy_side_abc(cy, abc);
    if (!solve_quadratic(abc, &t0, &t1))
        return false;
    if (cy->min <= t0 && t0 <= cy->max && judge_t(cy, &tmp, t0))
    {
        *hit = tmp;
        found = true;
    }
    if (cy->min <= t1 && t1 <= cy->max && judge_t(cy, &tmp, t1))
    {
        if (!found || tmp.dist < hit->dist)
            *hit = tmp;
        found = true;
    }
    return found;
}

/*
** hit_cy_caps
** 円柱のキャップ（上面・下面）の交差判定
** 1. 上キャップ中心 = center + axis * half_h
** 2. 下キャップ中心 = center - axis * half_h
** 3. それぞれのキャップについて hit_cy_cap() を呼ぶ
** 4. ヒットした場合は距離を比較して、より近いものを採用
**    → cy->max を更新
** ※ 法線は
**    上キャップ → +axis
**    下キャップ → -axis
*/
bool	hit_cy_caps(t_cy *cy, t_hit_point *hit)
{
	t_hit_point	tmp;
	t_xyz		top;
	t_xyz		bottom;
	bool		found;

	top = vec_add(cy->obj->xyz, vec_scale(cy->axis, cy->half_h));
	bottom = vec_sub(cy->obj->xyz, vec_scale(cy->axis, cy->half_h));
	found = false;
	if (hit_cy_cap(cy, top, cy->axis, HIT_CY_CAP_TOP, &tmp))
	{
		*hit = tmp;
		found = true;
	}
	if (hit_cy_cap(cy, bottom, vec_scale(cy->axis, -1.0),
		HIT_CY_CAP_BOTTOM, &tmp))
	{
		if (!found || tmp.dist < hit->dist)
			*hit = tmp;
		found = true;
	}
	return (found);
}

// denom = レイと平面の向きの関係（どれくらい当たるか）
/*
** hit_cy_cap
** 円柱キャップ（円盤）とレイの交差判定
** 1. レイと平面の交差を求める
**    → t = (center - origin)・normal / (dir・normal)
** 2. レイが平面と平行ならヒットしない
** 3. t が min/max 範囲内か確認（手前・奥の制限）
** 4. 交点 P = origin + t * dir を求める
** 5. P がキャップの円内にあるか確認
**    → |P - center|² <= radius²
** 6. ヒット情報（距離・位置・法線）を設定
*/
bool	hit_cy_cap(t_cy *cy, t_xyz center, t_xyz normal, t_hit_part part,
	t_hit_point *hit)
{
	double	denom;
	double	t;
	t_xyz	position;
	t_xyz	direction;

	denom = dot(cy->ray.dir, normal);
	if (fabs(denom) < EPS)
		return (false);
	t = dot(vec_sub(center, cy->ray.pos), normal) / denom;
	if (t < cy->min || cy->max < t)
		return (false);
	position = vec_add(cy->ray.pos, vec_scale(cy->ray.dir, t));
	direction = vec_sub(position, center);
	if (vec_length_sq(direction) > sqr(cy->radius))
		return (false);
	hit->dist = t;
	hit->pos = position;
	hit->norm = normal;
	hit->part = part;
	return (true);
}

// cylinder side quadratic coefficients
/*
** calc_cy_side_abc
** 円柱側面の交差判定に必要な二次方程式の係数 a, b, c を計算
** レイを円柱の式に代入すると
**    a t^2 + b t + c = 0
** という形になる
** 1. oc = ray.origin - cylinder.center
** 2. 円柱軸方向成分を除いたベクトルを使って計算
**    → cross を使うことで軸方向を排除
** 3. a, b, c を求める
** ※ この係数は solve_quadratic() に渡す
*/
void	calc_cy_side_abc(t_cy *cy, double abc[3])
{
	t_xyz	oc;
	t_xyz	d_cross;
	t_xyz	oc_cross;

	oc = vec_sub(cy->ray.pos, cy->obj->xyz);
	d_cross = cross(cy->ray.dir, cy->axis);
	oc_cross = cross(oc, cy->axis);
	// abc[0] = vec_length_sq(cross(cy->ray.dir, cy->axis));
	// abc[1] = 2.0 * dot(cross(cy->ray.dir, cy->axis), cross(oc, cy->axis));
	// abc[2] = vec_length_sq(cross(oc, cy->axis)) - sqr(cy->radius);
	abc[0] = dot(d_cross, d_cross);
	abc[1] = 2.0 * dot(d_cross, oc_cross);
	abc[2] = dot(oc_cross, oc_cross) - cy->radius * cy->radius;
}

// ** 4. 交点 P を求める
// ** 5. 軸方向距離 s を計算
// **    → s = (P - center)・axis
// ** 6. -half_h <= s <= half_h を満たすか確認
// **    → 円柱の高さ範囲内かチェック
// ** 7. 側面法線を計算
// **    → 軸からの放射方向
bool	judge_t(t_cy *cy, t_hit_point *hit, double t)
{
	t_xyz	pos;
	double	s;

	pos = vec_add(cy->ray.pos, vec_scale(cy->ray.dir, t));
	s = dot(vec_sub(pos, cy->obj->xyz), cy->axis);
	if (-cy->half_h <= s && s <= cy->half_h)
	{
		hit->dist = t;
		hit->pos = pos;
		hit->norm = normalize(vec_sub(pos,
			vec_add(cy->obj->xyz, vec_scale(cy->axis, s))));
		hit->part = HIT_CY_SIDE;
		// if (dot(hit->norm, cy->ray.dir) > 0)
		// 	hit->norm = vec_scale(hit->norm, -1.0);
		return (true);
	}
	return (false);
}
