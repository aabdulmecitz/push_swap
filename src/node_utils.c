/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:00:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 00:00:00 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(int value, t_gc *gc)
{
	t_node	*new_node;

	new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->keep = 0;
	return (new_node);
}

void	append_node(t_node **head, t_node *new_node)
{
	t_node	*tail;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
	new_node->prev = tail;
}
