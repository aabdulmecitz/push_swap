/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:38:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:38:47 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	gc_remove(t_gc *gc, void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!gc || !ptr || !gc->head)
		return ;
	prev = NULL;
	current = gc->head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gc->head = current->next;
			free(current);
			gc->count--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*current;
	t_gc_node	*next;
	int			freed_count;

	freed_count = 0;
	if (!gc)
		return ;
	current = gc->head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			freed_count++;
		}
		free(current);
		current = next;
	}
	gc->head = NULL;
	gc->count = 0;
}