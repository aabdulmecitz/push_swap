/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 01:53:42 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    sort_three(t_node **a)
{
    int	first;
    int	second;
    int	third;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;
    if (first > second && second < third && first < third)
        sa(a, true);
    else if (first > second && second > third && first > third)
    {
        sa(a, true);
        rra(a, true);
    }
    else if (first > second && second < third && first > third)
        ra(a, true);
    else if (first < second && second > third && first < third)
    {
        sa(a, true);
        ra(a, true);
    }
    else if (first < second && second > third && first > third)
        rra(a, true);
}

int	find_cheapest_element(t_node *stack_b)
{
	int		cheapest_cost;
	int		cheapest_index;
	int		index;
	t_node	*current;

	cheapest_cost = INT_MAX;
	cheapest_index = 0;
	index = 0;
	current = stack_b;
	while (current)
	{
		if (current->cost < cheapest_cost)
		{
			cheapest_cost = current->cost;
			cheapest_index = index;
		}
		current = current->next;
		index++;
	}
	return (cheapest_index);
}

void	sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	int		cheapest_index;
	int		i;
	int		stack_size;

	(void)gc;
	stack_size = get_stack_size(*stack_a);
	if (stack_size <= 3)
	{
		if (stack_size == 2)
		{
			if ((*stack_a)->value > (*stack_a)->next->value)
				sa(stack_a, true);
		}
		else if (stack_size == 3)
			sort_three(stack_a);
		return ;
	}
	move_to_b(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		calculate_costs(*stack_a, *stack_b);
		cheapest_index = find_cheapest_element(*stack_b);
		i = 0;
		while (i < cheapest_index)
		{
			rb(stack_b, true);
			i++;
		}
		pa(stack_a, stack_b, true);
	}
	while ((*stack_a)->index != 0)
	{
		ra(stack_a, true);
	}
}
