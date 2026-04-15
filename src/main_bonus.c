/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 06:37:19 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/15 13:41:55 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ui.h"
#include "raytracing.h"
#include "calc.h"

void	check_argv(int argc, char **argv)
{
	char	*filename;

	if (argc != 2)
		print_error_and_exit("main", "1 argument required");
	filename = argv[1];
	while (filename)
	{
		if (ft_memcmp(filename, "./", 2) == 0)
			filename += 2;
		else if (ft_memcmp(filename, "../", 3) == 0)
			filename += 3;
		else
			break ;
	}
	while (*filename != '.')
		filename++;
	if (ft_memcmp(filename, ".rt", 4))
		print_error_and_exit("main", "*.rt file required");
}

int	main(int argc, char **argv)
{
	int		part;
	t_env	*env;
	t_obj	*obj;

	check_argv(argc, argv);
	part = BONUS;
	parser(argv[1], part);
	env = set_get_env(GET, NULL);
	obj = set_get_obj(GET, NULL);
	init_window(obj, env);
	return (0);
}
