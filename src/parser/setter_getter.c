/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:25:16 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 15:18:38 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_env	*set_get_env(int select, t_env *new)
{
	static t_env	*tmp;

	if (select == SET)
		tmp = new;
	return (tmp);
}

t_lit	*set_get_lit(int select, t_lit *new)
{
	static t_lit	*tmp;

	if (select == SET)
		tmp = new;
	return (tmp);
}

t_obj	*set_get_obj(int select, t_obj *new)
{
	static t_obj	*tmp;

	if (select == SET)
		tmp = new;
	return (tmp);
}
