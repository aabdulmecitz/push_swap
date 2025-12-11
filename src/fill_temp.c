/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:09:32 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:09:33 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_single_number(t_node **temp_head, const char *str, t_gc *gc)
{
	t_node	*new_node;

	if (!is_valid_int(str))
		return (ft_perror("Error\n"), 0);
	new_node = create_node(ft_atoi(str), gc);
	if (!new_node)
		return (ft_perror("Error\n"), 0);
	append_node(temp_head, new_node);
	return (1);
}

static int	handle_arg(t_node **temp_head, const char *arg, t_gc *gc)
{
	int	num_count;

	num_count = count_numbers(arg);
	if (num_count < 0)
		return (ft_perror("Error\n"), 0);
	if (num_count > 1 || ft_strlen(arg) > 11)
		return (parse_space_separated(temp_head, arg, gc));
	return (parse_single_number(temp_head, arg, gc));
}

int	fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!handle_arg(temp_head, argv[i], gc))
			return (0);
		i++;
	}
	return (1);
}
