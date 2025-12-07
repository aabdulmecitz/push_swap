/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:15:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:28:22 by aozkaya          ###   ########.fr       */
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
		return (best_pos + 1);
	return (0);
}

void calculate_costs(t_node *stack_a, t_node *stack_b)
{
    t_node  *current_b;
    int     size_a;
    int     size_b;
    int     pos_b;
    int     cost_a;
    int     cost_b;

    size_a = get_stack_size(stack_a);
    size_b = get_stack_size(stack_b);
    current_b = stack_b;
    pos_b = 0;
    while (current_b)
    {
        current_b->target_pos_a = find_target_position(stack_a, current_b->index);
        
        // B stack'te de pozisyon hesapla
        cost_b = pos_b;
        if (pos_b > size_b / 2)
            cost_b = size_b - pos_b;
        
        // A stack'te target pozisyonuna gitme maliyeti
        cost_a = current_b->target_pos_a;
        if (current_b->target_pos_a > size_a / 2)
            cost_a = size_a - current_b->target_pos_a;
        
        // Toplam maliyet
        current_b->cost = cost_a + cost_b;
        
        current_b = current_b->next;
        pos_b++;
    }
}

void	print_costs(t_node *stack_a, t_node *stack_b)
{
	t_node	*current_a;
	t_node	*current_b;
	int		pos_b;

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
	ft_putstr_fd("\n\nCosts to place each B element in A:\n", 2);
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
		ft_putstr_fd(" (cost: ", 2);
		ft_putnbr_fd(current_b->cost, 2);
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
