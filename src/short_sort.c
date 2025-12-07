/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:41:01 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_max(t_node *stack)
{
	t_node	*max_node;

	if (!stack)
		return (NULL);
	max_node = stack;
	while (stack)
	{
		if (stack->value > max_node->value)
			max_node = stack;
		stack = stack->next;
	}
	return (max_node);
}

void	sort_three(t_node **a)
{
	t_node	*max_node;

	max_node = find_max(*a);
	if (max_node == *a)
		ra(a, true);
	else if ((*a)->next == max_node)
		rra(a, true);
	if ((*a)->value > (*a)->next->value)
		sa(a, true);
}

void	sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	(void)gc;
	if (is_sorted(*stack_a))
		return ;
	
	move_to_b(stack_a, stack_b);
	sort_three(stack_a);
	
	calculate_costs(*stack_a, *stack_b);
	print_costs(*stack_a, *stack_b);
}
    