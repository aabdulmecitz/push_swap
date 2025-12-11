/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:09:01 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:09:03 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	position_of_index(t_node *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

static int	find_min_pos(t_node *a)
{
	int	min_idx;
	int	min_pos;
	int	pos;

	min_idx = INT_MAX;
	min_pos = 0;
	pos = 0;
	while (a)
	{
		if (a->index < min_idx)
		{
			min_idx = a->index;
			min_pos = pos;
		}
		a = a->next;
		pos++;
	}
	return (min_pos);
}

static int	find_best_pos(t_node *a, int b_idx, int *best_idx)
{
	int	pos;
	int	best_pos;

	pos = 0;
	best_pos = -1;
	*best_idx = INT_MAX;
	while (a)
	{
		if (a->index > b_idx && a->index < *best_idx)
		{
			*best_idx = a->index;
			best_pos = pos;
		}
		a = a->next;
		pos++;
	}
	return (best_pos);
}

int	find_target_position(t_node *stack_a, int b_index)
{
	int	best_idx;
	int	best_pos;
	int	min_pos;

	best_pos = find_best_pos(stack_a, b_index, &best_idx);
	if (best_pos != -1)
		return (best_pos);
	min_pos = find_min_pos(stack_a);
	return (min_pos);
}
