/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:08:29 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:08:31 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calculate_rotation_cost(int pos, int size)
{
	if (size == 0)
		return (0);
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

int	get_rotation_direction(int pos, int size)
{
	if (size == 0)
		return (1);
	if (pos <= size / 2)
		return (1);
	return (-1);
}

t_cost	calculate_cost(int target_pos_a, int pos_b, int size_a, int size_b)
{
	t_cost	cost;

	cost.cost_a = calculate_rotation_cost(target_pos_a, size_a);
	cost.cost_b = calculate_rotation_cost(pos_b, size_b);
	cost.direction_a = get_rotation_direction(target_pos_a, size_a);
	cost.direction_b = get_rotation_direction(pos_b, size_b);
	if (cost.direction_a == cost.direction_b)
	{
		if (cost.cost_a > cost.cost_b)
			cost.total_cost = cost.cost_a;
		else
			cost.total_cost = cost.cost_b;
	}
	else
		cost.total_cost = cost.cost_a + cost.cost_b;
	return (cost);
}
