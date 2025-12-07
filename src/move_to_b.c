/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:11:33 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:41:01 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void move_to_b(t_node **stack_a, t_node **stack_b)
{
    int size;

    size = get_stack_size(*stack_a);
    while (size - get_stack_size(*stack_b) > 3)
    {
        pb(stack_a, stack_b, true);
    }
}