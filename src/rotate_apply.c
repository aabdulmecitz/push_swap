/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:08:55 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:08:56 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_both_forward(t_node **a, t_node **b, t_cost *c)
{
	while (c->direction_a == 1 && c->direction_b == 1
		&& c->cost_a > 0 && c->cost_b > 0)
	{
		rr(a, b, true);
		c->cost_a--;
		c->cost_b--;
	}
}

static void	rotate_both_backward(t_node **a, t_node **b, t_cost *c)
{
	while (c->direction_a == -1 && c->direction_b == -1
		&& c->cost_a > 0 && c->cost_b > 0)
	{
		rrr(a, b, true);
		c->cost_a--;
		c->cost_b--;
	}
}

void	apply_rotation(t_node **stack_a, t_node **stack_b, t_cost cost)
{
	rotate_both_forward(stack_a, stack_b, &cost);
	rotate_both_backward(stack_a, stack_b, &cost);
	while (cost.cost_a-- > 0)
	{
		if (cost.direction_a == 1)
			ra(stack_a, true);
		else
			rra(stack_a, true);
	}
	while (cost.cost_b-- > 0)
	{
		if (cost.direction_b == 1)
			rb(stack_b, true);
		else
			rrb(stack_b, true);
	}
}

void	align_smallest_to_top(t_node **stack_a)
{
	int	size;
	int	pos_min;

	size = get_stack_size(*stack_a);
	pos_min = position_of_index(*stack_a, 1);
	if (pos_min < 0)
		return ;
	if (pos_min <= size / 2)
	{
		while (pos_min-- > 0)
			ra(stack_a, true);
	}
	else
	{
		pos_min = size - pos_min;
		while (pos_min-- > 0)
			rra(stack_a, true);
	}
}
