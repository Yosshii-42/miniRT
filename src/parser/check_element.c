/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:14:27 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/17 21:21:18 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_first_element(char *str)
{
	if ((*str == 'A' && str[1] == '\0') || (*str == 'C' && str[1] == '\0'))
		return (ENV);
	if ((*str == 'L' && str[1] == '\0'))
		return (LIT);
	if ((ft_strncmp(str, "sp", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "pl", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "cy", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "cn", 2) == 0 && str[2] == '\0'))
		return (OBJ);
	return (OTHER);
}

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	check_array_num(double arr[3], int select)
{
	if (select == VECTOR)
	{
		if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0)
			print_error_and_exit("vector", "invalid vector (0, 0, 0)");
		if (is_minus1_1(arr[0]) * is_minus1_1(arr[1])
			* is_minus1_1(arr[2]) == 0)
			print_error_and_exit("vector", "number is not between -1 and 1");
	}
	if (select == RGB)
	{
		if (is_0_255(arr[0]) * is_0_255(arr[1]) * is_0_255(arr[2]) == 0)
			print_error_and_exit("RGB", "number is not between 0 and 255");
	}
}

void	check_comma(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			count++;
	}
	if (count > 2)
		print_error_and_exit("set array", "too many \',\'");
	else if (count < 2)
		print_error_and_exit("set array", "too few \',\'");
}

bool	check_file(char *filename)
{
	if (!filename)
		print_error_and_exit("image file", "file name required");
	while (*filename && *filename != '.')
		filename++;
	if (!(ft_strncmp(filename, ".xpm", 4) == 0 && filename[4] == '\0'))
		print_error_and_exit("image file", "\'.xpm\' file required");
	return (true);
}
