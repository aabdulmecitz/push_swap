/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:29:31 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:41:01 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_gc	*create_local_gc(t_gc **local_gc)
{
	*local_gc = (t_gc *)malloc(sizeof(t_gc));
	if (!*local_gc)
		return (ft_perror("Error\n"), NULL);
	gc_init(*local_gc);
	return (*local_gc);
}

static void	cleanup_gc(t_gc *gc, t_gc *local_gc)
{
	gc_free_all(gc);
	if (local_gc)
		free(local_gc);
}

static int	build_temp(t_node **temp_head, char **argv,
			t_gc *gc, t_gc *local_gc)
{
	*temp_head = NULL;
	if (!fill_temp_stack(temp_head, argv, gc))
		return (cleanup_gc(gc, local_gc), 0);
	if (!check_values(*temp_head))
		return (ft_perror("Error\n"), cleanup_gc(gc, local_gc), 0);
	return (1);
}

t_gc	*init_stacks(t_node **stack_a, t_node **stack_b, char **argv, t_gc *gc)
{
	t_gc	*local_gc;
	t_node	*temp_head;

	local_gc = NULL;
	if (!gc)
		gc = create_local_gc(&local_gc);
	if (!gc)
		return (NULL);
	*stack_a = NULL;
	*stack_b = NULL;
	if (!argv || !argv[1])
	{
		ft_perror("Error\n");
		cleanup_gc(gc, local_gc);
		return (NULL);
	}
	if (!build_temp(&temp_head, argv, gc, local_gc))
		return (NULL);
	if (!init_a_stack(stack_a, temp_head, gc))
	{
		cleanup_gc(gc, local_gc);
		return (NULL);
	}
	return (local_gc);
}
