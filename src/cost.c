/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:15:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 01:53:42 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_size(t_node *stack)
{
	int		size;
	t_node	*current;

	size = 0;
	current = stack;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	get_position(t_node *stack, int value)
{
	int		position;
	t_node	*current;

	position = 0;
	current = stack;
	while (current)
	{
		if (current->value == value)
			return (position);
		position++;
		current = current->next;
	}
	return (-1);
}

static int	find_target_position(t_node *stack_a, int value)
{
	int		position;
	t_node	*current;
	t_node	*best_node;
	int		best_pos;

	position = 0;
	best_node = NULL;
	best_pos = 0;
	current = stack_a;
	while (current)
	{
		if (current->index < value)
		{
			if (!best_node || current->index > best_node->index)
			{
				best_node = current;
				best_pos = position;
			}
		}
		position++;
		current = current->next;
	}
	if (!best_node)
		best_pos = 0;
	return (best_pos);
}

static int	calculate_rotation_cost(int position, int stack_size)
{
	int	cost_forward;
	int	cost_backward;

	cost_forward = position;
	cost_backward = stack_size - position;
	if (cost_forward < cost_backward)
		return (cost_forward);
	return (cost_backward);
}

int	calculate_cost_for_element(t_node *stack_a, t_node *stack_b, int b_position)
{
	int		size_a;
	int		size_b;
	int		target_pos_a;
	int		cost_a;
	int		cost_b;
	int		cost_rotate_both;
	int		total_cost;
	t_node	*b_element;

	size_a = get_stack_size(stack_a);
	size_b = get_stack_size(stack_b);
	cost_b = calculate_rotation_cost(b_position, size_b);
	
	b_element = stack_b;
	while (b_position-- > 0)
		b_element = b_element->next;
	
	target_pos_a = find_target_position(stack_a, b_element->index);
	cost_a = calculate_rotation_cost(target_pos_a, size_a);
	
	cost_rotate_both = (cost_a > cost_b) ? cost_a : cost_b;
	total_cost = cost_rotate_both + (cost_a + cost_b - 2 * cost_rotate_both);
	
	return (total_cost);
}

void    calculate_costs(t_node *stack_a, t_node *stack_b)
{
    t_node  *current_b;
    int     position_b;

    current_b = stack_b;
    position_b = 0;
    while (current_b)
    {
        current_b->cost = calculate_cost_for_element(stack_a, stack_b, position_b);
        current_b = current_b->next;
        position_b++;
    }
}
