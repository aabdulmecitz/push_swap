/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:27 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:24:11 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	t_gc	*gc;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (1);
	(void)argc;
	gc = init_stacks(&stack_a, &stack_b, argv, NULL);
	if (!gc)
		return (1);
	if (!is_sorted(stack_a))
		sort_stacks(&stack_a, &stack_b, gc);
	if (!stack_a)
		return (gc_free_all(gc), 0);
	if (gc)
		(gc_free_all(gc), free(gc));
	return (0);
}
