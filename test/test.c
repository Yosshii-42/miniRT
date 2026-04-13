#include "calc.h"

void    calc_test()
{
    t_xyz   v1;
    t_xyz   v2;
    t_xyz   tmp;
    double  f = 3.0f;
    double  ans;

    v1.x = 1;
    v1.y = 2;
    v1.z = 3;
    v2.x = 4;
    v2.y = 5;
    v2.z = 6;
    printf("\n** calculator check **\n");
    printf("v1 = (1, 2, 3) v2 = (4, 5, 6) f = 3.0f\n");
    ans = dot(v1, v2);
    printf("dot(v1, v2) = %f\n   expected: 32\n", ans);
    tmp = cross(v1, v2);
    printf("cross(v1, v2) = (%f, %f, %f)\n   expected: (-3, 6, -3)\n", tmp.x, tmp.y, tmp.z);
    tmp = vec_mul(v1, v2);
    printf("vec_mul(v1, v2) = (%f, %f, %f)\n   expected: (4, 10, 18)\n", tmp.x, tmp.y, tmp.z);
    tmp = vec_scale(v1, f);
    printf("vec_scale(v1, f) = (%f, %f, %f)\n   expected: (3, 6, 9)\n", tmp.x, tmp.y, tmp.z);
    tmp = divid_v1_v2(v1, v2);
    printf("divid_v1_v2(v1, v2) = (%f, %f, %f)\n   expected: (0.25, 0.4, 0.5)\n", tmp.x, tmp.y, tmp.z);
    tmp = vec_div(v1, f);
    printf("vec_div(v1, f) = (%f, %f, %f)\n   expected: (0.333333, 0.666667, 1.0)\n", tmp.x, tmp.y, tmp.z);
    tmp = vec_add(v1, v2);
    printf("vec_add(v1, v2) = (%f, %f, %f)\n   expected: (5, 7, 9)\n", tmp.x, tmp.y, tmp.z);
    tmp = plus_v_f(v1, f);
    printf("plus_v_f(v1, f) = (%f, %f, %f)\n   expected: (4, 5, 6)\n", tmp.x, tmp.y, tmp.z);
    tmp = vec_sub(v1, v2);
    printf("vec_sub(v1, v2) = (%f, %f, %f)\n   expected: (-3, -3, -3)\n", tmp.x, tmp.y, tmp.z);
    tmp = minus_v_f(v1, f);
    printf("minus_v_f(v1, f) = (%f, %f, %f)\n   expected: (-2, -1, 0)\n", tmp.x, tmp.y, tmp.z);
    v1.x = 3;
    v1.y = 4;
    v1.z = 5;    
    printf("v1 = (3, 4, 5)\n");
    ans = sqr(v1.x);
    printf("sqr(v1.x) = %f\n   expected: 9\n", ans);
    ans = vec_length_sq(v1);
    printf("vec_length_sq(v1) = %f\n   expected: 50\n", ans);
    ans = vec_length(v1);
    printf("vec_length(v1) = %f\n   expected: 7.071068\n", ans);
    tmp = normalize(v1);
    printf("normalize(v1) = (%f, %f, %f)\n   expected: (0.424264, 0.565685, 0.707107)\n", tmp.x, tmp.y, tmp.z);
}
