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

static t_node	*find_max(t_node *stack)
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

static void	push_non_keep(t_node **a, t_node **b)
{
	int		len;
	int		i;

	len = get_stack_size(*a);
	i = 0;
	while (i < len)
	{
		if ((*a)->keep == 0)
			pb(a, b, true);
		else
			ra(a, true);
		i++;
	}
}

void	sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	(void)gc;
	if (is_sorted(*stack_a))
		return ;
	if (get_stack_size(*stack_a) <= 3)
		return (sort_three(stack_a));
	mark_lis_nodes(*stack_a);
	push_non_keep(stack_a, stack_b);
	if (get_stack_size(*stack_a) == 2 && !is_sorted(*stack_a))
		sa(stack_a, true);
	else if (get_stack_size(*stack_a) >= 3)
		sort_three(stack_a);
	while (*stack_b)
		move_best_from_b(stack_a, stack_b);
	align_smallest_to_top(stack_a);
}
    