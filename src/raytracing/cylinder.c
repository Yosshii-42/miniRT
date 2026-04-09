
#include "calc.h"
#include "parser.h"
#include "raytracing.h"

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
bool	hit_cy_core(t_cy *cy, t_hit_point *hit) {
	t_hit_point	tmp;
	bool		found;

	found = false;
	if (hit_cy_side(cy, &tmp))
	{
		*hit = tmp;
		cy->max = tmp.dist;
		found = true;
	}
	if (hit_cy_caps(cy, &tmp))
	{
		*hit = tmp;
		found = true;
	}
	return (found);
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

	top = plus_v1_v2(cy->obj->xyz, multi_v_f(cy->axis, cy->half_h));
	bottom = minus_v1_v2(cy->obj->xyz, multi_v_f(cy->axis, cy->half_h));
	found = false;
	if (hit_cy_cap(cy, top, cy->axis, &tmp))
	{
		*hit = tmp;
		cy->max = tmp.dist;
		found = true;
	}
	if (hit_cy_cap(cy, bottom, multi_v_f(cy->axis, -1.0), &tmp))
	{
		*hit = tmp;
		cy->max = tmp.dist;
		found = true;
	}
	return (found);
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

	oc = minus_v1_v2(cy->ray.pos, cy->obj->xyz);
	abc[0] = squared_norm(cross(cy->ray.dir, cy->axis));
	abc[1] = 2.0 * dot(cross(cy->ray.dir, cy->axis), cross(oc, cy->axis));
	abc[2] = squared_norm(cross(oc, cy->axis)) - sqr(cy->radius);
}

/*
** hit_cy_side
**
** 円柱側面とレイの交差判定
** 1. 無限円柱との交差を二次方程式で求める
**    → a t² + b t + c = 0
** 2. 解の公式で t0, t1 を求める
** 3. min <= t <= max を満たす解を選ぶ
** 4. 交点 P を求める
** 5. 軸方向距離 s を計算
**    → s = (P - center)・axis
** 6. -half_h <= s <= half_h を満たすか確認
**    → 円柱の高さ範囲内かチェック
** 7. 側面法線を計算
**    → 軸からの放射方向
*/
bool	hit_cy_side(t_cy *cy, t_hit_point *hit)
{
	double	abc[3];
	double	t[2];
	double	s;

	calc_cy_side_abc(cy, abc);
	if (!solve_quadratic(abc, &t[0], &t[1]))
		return (false);
	if (cy->min <= t[0] && t[0] <= cy->max)
		hit->dist = t[0];
	else if (cy->min <= t[1] && t[1] <= cy->max)
		hit->dist = t[1];
	else
		return (false);
	hit->pos = plus_v1_v2(cy->ray.pos, multi_v_f(cy->ray.dir, hit->dist));
	s = dot(minus_v1_v2(hit->pos, cy->obj->xyz), cy->axis);
	if (s < -cy->half_h || cy->half_h < s)
		return (false);
	hit->norm = normalize(minus_v1_v2(hit->pos,
		plus_v1_v2(cy->obj->xyz, multi_v_f(cy->axis, s))));
	return (true);
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
bool			hit_cy_cap(t_cy *cy, t_xyz center, t_xyz normal, t_hit_point *hit)
{
	double	denom;
	double	t;
	t_xyz	position;
	t_xyz	direction;

	denom = dot(cy->ray.dir, normal);
	if (fabs(denom) < EPS)
		return (false);
	t = dot(minus_v1_v2(center, cy->ray.pos), normal) / denom;
	if (t < cy->min || cy->max < t)
		return (false);
	position = plus_v1_v2(cy->ray.pos, multi_v_f(cy->ray.dir, t));
	direction = minus_v1_v2(position, center);
	if (squared_norm(direction) > sqr(cy->radius))
		return (false);
	hit->dist = t;
	hit->pos = position;
	hit->norm = normal;
	return (true);
}
