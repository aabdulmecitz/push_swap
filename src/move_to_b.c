/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:11:33 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 01:12:00 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void move_to_b(t_node **stack_a, t_node **stack_b)
{
    int size;
    int pushed;
    int i;

    size = get_stack_size(*stack_a);
    pushed = 0;
    i = 0;
    while (size > 6 && i < size && pushed < size / 2)
    {
        if ((*stack_a)->index <= size / 2)
        {
            pb(stack_a, stack_b, true);
            pushed++;
        }
        else
            ra(stack_a, true);
        i++;
    }
    while (size - pushed > 3)
    {
        pb(stack_a, stack_b, true);
        pushed++;
    }
}