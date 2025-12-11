/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:08:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:08:39 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_target	find_cheapest_target(t_node *stack_a, t_node *stack_b)
{
	t_target	best;
	t_target	cur;
	t_node		*node_b;
	int			pos_b;
	int			size_a;

	node_b = stack_b;
	pos_b = 0;
	size_a = get_stack_size(stack_a);
	best.index = -1;
	while (node_b)
	{
		cur.index = node_b->index;
		cur.target_pos_a = find_target_position(stack_a, cur.index);
		cur.target_pos_b = pos_b;
		cur.move_cost = calculate_cost(cur.target_pos_a, pos_b,
				size_a, get_stack_size(stack_b));
		if (best.index == -1
			|| cur.move_cost.total_cost < best.move_cost.total_cost)
			best = cur;
		node_b = node_b->next;
		pos_b++;
	}
	return (best);
}

void	move_best_from_b(t_node **stack_a, t_node **stack_b)
{
	t_target	best;
	t_node		*node;
	int			pos_b;

	best = find_cheapest_target(*stack_a, *stack_b);
	if (best.index < 0)
		return ;
	node = *stack_b;
	pos_b = 0;
	while (node && node->index != best.index)
	{
		node = node->next;
		pos_b++;
	}
	if (!node)
		return ;
	best.target_pos_b = pos_b;
	best.move_cost = calculate_cost(best.target_pos_a, pos_b,
			get_stack_size(*stack_a), get_stack_size(*stack_b));
	apply_rotation(stack_a, stack_b, best.move_cost);
	pa(stack_a, stack_b, true);
}
