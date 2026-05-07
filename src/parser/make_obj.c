/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:20:41 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/26 15:05:33 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	obj_lst_add_back(t_obj *obj, t_obj *new)
{
	if (!obj)
	{
		obj = new;
		set_get_obj(SET, obj);
		return ;
	}
	while (obj->next)
		obj = obj->next;
	obj->next = new;
}

void	make_obj_data(char **split, int part)
{
	t_obj	*obj;
	t_obj	*new;

	obj = set_get_obj(GET, NULL);
	new = (t_obj *)safe_malloc(1, sizeof(t_obj));
	init_obj(new);
	new->count = count_split(split);
	if (ft_strncmp(split[0], "pl", 2) == 0 && split[0][2] == '\0')
		set_pl_data(split, new, part);
	else if (ft_strncmp(split[0], "sp", 2) == 0 && split[0][2] == '\0')
		set_sp_data(split, new, part);
	else if (ft_strncmp(split[0], "cy", 2) == 0 && split[0][2] == '\0')
		set_cy_data(split, new);
	else if (part == BONUS && ft_strncmp(split[0], "cn", 2) == 0
		&& split[0][2] == '\0')
		set_cn_data(split, new);
	else
		print_error_and_exit("object", "invalid identifier");
	obj_lst_add_back(obj, new);
}
