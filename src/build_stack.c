/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:00:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 00:00:00 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calc_index(t_node *head, int value)
{
	int	index;

	index = 1;
	while (head)
	{
		if (head->value < value)
			index++;
		head = head->next;
	}
	return (index);
}

int	init_a_stack(t_node **a, t_node *temp_head, t_gc *gc)
{
	t_node	*current;
	t_node	*new_node;

	current = temp_head;
	while (current)
	{
		new_node = create_node(current->value, gc);
		if (!new_node)
			return (ft_perror("Error\n"), 0);
		new_node->index = calc_index(temp_head, current->value);
		append_node(a, new_node);
		current = current->next;
	}
	return (1);
}
