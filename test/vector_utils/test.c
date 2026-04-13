#include <stdio.h>
#include "vector_utils.h"
#include <math.h>
 
#define WIDTH 512
#define HEIGHT 512



double	convert_screen_pos_x(int sc_x)
{
	double	ret;

	ret = 2 * sc_x;
	ret = ret / (WIDTH - 1) - 1;
	return (ret);
}

double	convert_screen_pos_y(int sc_y)
{
	double	ret;

	ret = -2 * sc_y;
	ret = ret / (HEIGHT - 1) + 1;
	return (ret);
}

double	convert_screen_pos_z(int pixel)
{
	return (0);
}

int main()
{
	//vector_t	pw;

	//int	x_s = 382;
	//int	y_s = 255;
	////スクリーン上の座標を 3 次元空間上の座標に変換する
	//pw.x = convert_screen_pos_x(x_s);
	//pw.y = convert_screen_pos_y(y_s);
	//pw.z = 0;
	//printf("(%d,%d) -> %s\n", x_s, y_s, vector_str(&pw));


	vector_t eye_pos    = { 0, 0, -5 };/* 視点位置 */
	vector_t sphere_pos = { 0, 0, 5 };  /* 球の中心 */
	float sphere_r = 1;                 /* 球の半径 */
	vector_t pw         = { -0.4, 0, 0 };/* スクリーン上の点 */
	vector_t eye_dir; /* 視線方向ベクトル */
	vector_t s_c;     /* 視点 - 球の中心 */
	float A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	//視線方向ベクトルの計算
	eye_dir.x = pw.x - eye_pos.x;
	eye_dir.y = pw.y - eye_pos.y;
	eye_dir.z = pw.z - eye_pos.z;
	//eye_dir は視線方向のベクトルなので正規化をする
	normalize(&eye_dir);
	//点 B から点 A へ向かうベクトルを作成したいとき A - B を行う。
	//つまり、球の中心から視点へ向かうベクトル 
	s_c.x = eye_pos.x - sphere_pos.x;
	s_c.y = eye_pos.y - sphere_pos.y;
	s_c.z = eye_pos.z - sphere_pos.z;
	A = vec_length_sq(&eye_dir);
	B = 2 * dot(&eye_dir, &s_c);
	C = vec_length_sq(&s_c) - sphere_r * sphere_r;
	D = B * B - 4 * A * C;
	float t1 = (-B + sqrt(D)) / (2  * A);
	float t2 = (-B - sqrt(D)) / (2  * A);
	if (D >= 0 && (t1 > 0 || t2 > 0))
	{
		printf("Yes!\n");
	}
	else
	{
		printf("No...\n");
	}
	return 0;
}