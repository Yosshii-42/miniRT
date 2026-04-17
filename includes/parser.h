/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 06:06:40 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/17 21:28:39 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "libft.h"
# include "types.h"

# define MANDATORY 0
# define BONUS 1
# define SET 0
# define GET 1
# define ENV 0
# define LIT 1
# define OBJ 2
# define OTHER 3
# define VECTOR 4
# define RGB 5
# define SPACE "\t\n\v\r\f "
# define DBL_MAX 1.7976931348623158e+308
# define DBL_MIN 2.2250738585072014e-308

//check_element.c
int				check_first_element(char *str);
int				count_split(char **split);
void			check_array_num(double arr[3], int select);
void			check_comma(char *str);
bool			check_file(char *filename);

//check_range.c
bool			is_minus1_1(double num);
bool			is_0_1(double num);
bool			is_0_180(double num);
bool			is_0_255(double num);

//free.c
void			free_split(char **split);
void			free_lit(t_lit *lit);
void			free_obj(t_obj *obj, t_mlx_env *mlx);

//ft_atof.c
double			ft_atof(char *nptr);

//init.c
void			init_meta_img(t_meta_img *tex);
void			init_xyz(t_xyz *xyz);
void			init_env(t_env *env, t_lit *lit, int part);
void			init_lit(t_lit *lit);
void			init_obj(t_obj *obj);

//make_env_data.c
void			make_env_data(char **split);
void			set_amb_data(char **split, t_env *env);
void			set_cam_data(char **split, t_env *env);

//make_lit_data.c
void			make_lit_data(char **split);
void			set_lit_data(char **split, t_lit *lit, t_env *env);
void			lit_lst_add_back(t_lit *lit, t_lit *new);

//make_obj.c
void			make_obj_data(char **split);
void			obj_lst_add_back(t_obj *obj, t_obj *new);

// make_obj_pl_sp.c
void			set_pl_data(char **split, t_obj *new);
void			set_sp_data(char **split, t_obj *new);
void			set_image(char *filename, t_obj *new);
void			set_texture(char **split, t_obj *new, int count);

//make_obj_cy_cn.c
void			set_cy_data(char **split, t_obj *new);
void			set_cn_data(char **split, t_obj *new);

//parser.c
void			parser(char *filename, int part);
void			init_parser_data(t_env *env, t_lit *lit, t_obj *obj, int part);
void			make_information(char *line);
void			set_array(char *str, double arr[3], int select);
void			set_struct_xyz(t_xyz *xyz, double arr[3]);

//print_function.c
void			print_error_and_exit(char *func_name, char *message);

//setter_getter.c
t_env			*set_get_env(int select, t_env *new);
t_lit			*set_get_lit(int select, t_lit *new);
t_obj			*set_get_obj(int select, t_obj *new);

//utils.c
void			open_file(char *file_name, int *fd);
void			*safe_malloc(size_t count, size_t size);
unsigned int	make_trgb(double t, double r, double g, double b);

#endif
