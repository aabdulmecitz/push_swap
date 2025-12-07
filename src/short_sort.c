/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:08:41 by aozkaya          ###   ########.fr       */
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

void	sort_stack(t_node **a, t_node **b)
{
	int	len;

	if (stack_sorted(*a))
		return ;
	len = stack_len(*a);
	if (len == 2)
		sa(a, true);
	else if (len == 3)
		sort_three(a);
	else
		sort_algorithm(a, b);
}