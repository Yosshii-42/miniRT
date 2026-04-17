/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:15:54 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/17 14:51:30 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);
	}
	if (split)
		free(split);
}

void	free_lit(t_lit *lit)
{
	t_lit	*tmp;

	if (lit)
	{
		while (lit)
		{
			tmp = lit->next;
			free(lit);
			lit = tmp;
		}
	}
}

void	free_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (obj)
	{
		while (obj)
		{
			tmp = obj->next;
			if (obj->filename)
				free(obj->filename);
			if (obj->tex.img)
				mlx_destroy_image(mlx->mlx, obj->tex.img);
			free(obj);
			obj = tmp;
		}
	}
}
