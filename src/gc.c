/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:37:36 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:06:57 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	gc_init(t_gc *gc)
{
	if (!gc)
		return ;
	gc->head = NULL;
	gc->count = 0;
}

void	gc_add(t_gc *gc, void *ptr)
{
	t_gc_node	*new_node;
	t_gc_node	*current;

	if (!gc || !ptr)
		return ;
	current = gc->head;
	while (current)
	{
		if (current->ptr == ptr)
			return ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
	gc->count++;
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	if (!gc)
		return (malloc(size));
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(gc, ptr);
	return (ptr);
}

char	*gc_strdup(t_gc *gc, const char *str)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = gc_malloc(gc, len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	gc_add_string_array(t_gc *gc, char **array)
{
	int	i;

	if (!array)
		return ;
	gc_add(gc, array);
	i = 0;
	while (array[i])
	{
		gc_add(gc, array[i]);
		i++;
	}
}
