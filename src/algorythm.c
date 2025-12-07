/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorythm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:13 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:09:14 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_algorithm(t_node **stack_a, t_node **stack_b)
{
    move_to_b(stack_a, stack_b);
    sort_three(stack_a);
    while (*stack_b)
    {
        calculate_costs(*stack_a, *stack_b);
        int cheapest_index = find_cheapest_element(*stack_b);
        t_node *current_b = *stack_b;
        int b_position = 0;
        while (current_b)
        {
            if (current_b->index == cheapest_index)
                break;
            b_position++;
            current_b = current_b->next;
        }
        calculate_cost_for_element(*stack_a, *stack_b, b_position);
        // Perform rotations and push based on calculated costs
        // (Implementation of rotations and push logic goes here)
    }
    // Final adjustments to rotate stack_a to sorted position
    // (Implementation of final rotation logic goes here)
}