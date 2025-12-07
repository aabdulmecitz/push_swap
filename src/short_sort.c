/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:29:22 by aozkaya          ###   ########.fr       */
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

void	sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	(void)gc;
	if (is_sorted(*stack_a))
		return ;
	
	ft_putstr_fd("\n=== AFTER move_to_b ===\n", 2);
	move_to_b(stack_a, stack_b);
	
	ft_putstr_fd("\n=== COST ANALYSIS - A'yı sırala sonra B'den al ===\n", 2);
	calculate_costs(*stack_a, *stack_b);
	print_costs(*stack_a, *stack_b);
}
