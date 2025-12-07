/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:15:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:56:09 by aozkaya          ###   ########.fr       */
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

static int	find_target_position(t_node *stack_a, int b_index)
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
		if (current->index < b_index)
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
	if (best_node)
	{
		return (best_pos);
	}
	return (0);
}

void calculate_costs(t_node *stack_a, t_node *stack_b)
{
    t_node  *current_b;
    int     size_b;
    int     size_a;
    int     pos_b;
    int     target_pos;
    int     forward_a;
    int     backward_a;
    int     forward_b;
    int     backward_b;
    int     cost_forward_forward;
    int     cost_forward_backward;
    int     cost_backward_forward;
    int     cost_backward_backward;
    int     min_cost;

    size_b = get_stack_size(stack_b);
    size_a = get_stack_size(stack_a);
    current_b = stack_b;
    pos_b = 0;
    while (current_b)
    {
        target_pos = find_target_position(stack_a, current_b->index);
        current_b->target_pos_a = target_pos;
        
        // Rotation costs for A (bringing target_pos to head)
        forward_a = target_pos;
        backward_a = size_a - target_pos;
        
        // Rotation costs for B (bringing element to top)
        forward_b = pos_b;
        backward_b = size_b - pos_b;
        
        // Calculate all combinations:
        // Forward-Forward (rr): can overlap with simultaneous rotation
        cost_forward_forward = (forward_a > forward_b ? forward_a : forward_b);
        
        // Forward A, Backward B (ra + rrb): no overlap
        cost_forward_backward = forward_a + backward_b;
        
        // Backward A, Forward B (rra + rb): no overlap
        cost_backward_forward = backward_a + forward_b;
        
        // Backward-Backward (rrr): can overlap with simultaneous rotation
        cost_backward_backward = (backward_a > backward_b ? backward_a : backward_b);
        
        // Find minimum cost
        min_cost = cost_forward_forward;
        if (cost_forward_backward < min_cost)
            min_cost = cost_forward_backward;
        if (cost_backward_forward < min_cost)
            min_cost = cost_backward_forward;
        if (cost_backward_backward < min_cost)
            min_cost = cost_backward_backward;
        
        current_b->cost = min_cost;
        
        current_b = current_b->next;
        pos_b++;
    }
}

void	print_costs(t_node *stack_a, t_node *stack_b)
{
	t_node	*current_a;
	t_node	*current_b;
	int		pos_a;
	int		pos_b;
	int		size_a;
	int		cost_rotate;
	int		total_b_cost;

	ft_putstr_fd("\n=== COST ANALYSIS ===\n", 2);
	ft_putstr_fd("Stack A (indices): ", 2);
	current_a = stack_a;
	while (current_a)
	{
		ft_putnbr_fd(current_a->index, 2);
		ft_putstr_fd(" ", 2);
		current_a = current_a->next;
	}
	ft_putstr_fd("\nStack B (indices): ", 2);
	current_b = stack_b;
	while (current_b)
	{
		ft_putnbr_fd(current_b->index, 2);
		ft_putstr_fd(" ", 2);
		current_b = current_b->next;
	}
	
	ft_putstr_fd("\n\nA elementlerinin kendi yerine gelmesi icin hamle sayisi:\n", 2);
	current_a = stack_a;
	pos_a = 0;
	size_a = get_stack_size(stack_a);
	while (current_a)
	{
		ft_putstr_fd("A[", 2);
		ft_putnbr_fd(pos_a, 2);
		ft_putstr_fd("] idx=", 2);
		ft_putnbr_fd(current_a->index, 2);
		ft_putstr_fd(" pos=", 2);
		ft_putnbr_fd(pos_a, 2);
		
		// A'daki ideal position (sorted order'da index'e göre)
		// Index 1 = pos 0, index 2 = pos 1, index 3 = pos 2, etc.
		int ideal_pos = current_a->index - 1;
		int cost_forward = (ideal_pos - pos_a + size_a) % size_a;
		int cost_backward = (pos_a - ideal_pos + size_a) % size_a;
		
		if (cost_forward == 0)
			cost_rotate = 0;
		else if (cost_forward <= cost_backward)
			cost_rotate = cost_forward;
		else
			cost_rotate = cost_backward;
		
		ft_putstr_fd(" -> ideal pos ", 2);
		ft_putnbr_fd(ideal_pos, 2);
		ft_putstr_fd(" (cost: ", 2);
		ft_putnbr_fd(cost_rotate, 2);
		ft_putstr_fd(")\n", 2);
		current_a = current_a->next;
		pos_a++;
	}
	
	ft_putstr_fd("\nB elementlerinin A'ya konmasi toplam hamle sayisi:\n", 2);
	current_b = stack_b;
	pos_b = 0;
	while (current_b)
	{
		ft_putstr_fd("B[", 2);
		ft_putnbr_fd(pos_b, 2);
		ft_putstr_fd("] idx=", 2);
		ft_putnbr_fd(current_b->index, 2);
		ft_putstr_fd(" -> A pos ", 2);
		ft_putnbr_fd(current_b->target_pos_a, 2);
		ft_putstr_fd(" (hamle: ", 2);
		total_b_cost = current_b->cost + 1;
		ft_putnbr_fd(total_b_cost, 2);
		ft_putstr_fd(")\n", 2);
		current_b = current_b->next;
		pos_b++;
	}
	ft_putstr_fd("===================\n\n", 2);
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
