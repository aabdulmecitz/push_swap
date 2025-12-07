/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:26:34 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:51:08 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_node **a, t_node **b, bool print)
{
	t_node	*push_node;

	if (!*b)
		return ;
	push_node = *b;
	*b = (*b)->next;
	if (*b)
		(*b)->prev = NULL;
	push_node->prev = NULL;
	push_node->next = *a;
	if (*a)
		(*a)->prev = push_node;
	*a = push_node;
	if (print)
		ft_perror("pa\n");
}

void	pb(t_node **a, t_node **b, bool print)
{
	t_node	*push_node;

	if (!*a)
		return ;
	push_node = *a;
	*a = (*a)->next;
	if (*a)
		(*a)->prev = NULL;
	push_node->prev = NULL;
	push_node->next = *b;
	if (*b)
		(*b)->prev = push_node;
	*b = push_node;
	if (print)
		ft_perror("pb\n");
}

void	ra(t_node **a, bool print)
{
	t_node	*last;

	if (!*a || !(*a)->next)
		return ;
	last = find_last(*a);
	last->next = *a;
	(*a)->prev = last;
	*a = (*a)->next;
	(*a)->prev = NULL;
	last->next->next = NULL;
	if (print)
		ft_perror("ra\n");
}

void	rb(t_node **b, bool print)
{
	t_node	*last;

	if (!*b || !(*b)->next)
		return ;
	last = find_last(*b);
	last->next = *b;
	(*b)->prev = last;
	*b = (*b)->next;
	(*b)->prev = NULL;
	last->next->next = NULL;
	if (print)
		ft_perror("rb\n");
}
