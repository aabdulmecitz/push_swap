/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:27:06 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:50:08 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulmecitz <aabdulmecitz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2025/11/18 20:56:35 by aabdulmecit      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_node **a, t_node **b, bool print)
{
	ra(a, false);
	rb(b, false);
	if (print)
		ft_perror("rr\n");
}

void	rra(t_node **a, bool print)
{
	t_node	*last;

	if (!*a || !(*a)->next)
		return ;
	last = find_last(*a);
	last->prev->next = NULL;
	last->next = *a;
	(*a)->prev = last;
	*a = last;
	(*a)->prev = NULL;
	if (print)
		ft_perror("rra\n", 1);
}

void	rrb(t_node **b, bool print)
{
	t_node	*last;

	if (!*b || !(*b)->next)
		return ;
	last = find_last(*b);
	last->prev->next = NULL;
	last->next = *b;
	(*b)->prev = last;
	*b = last;
	(*b)->prev = NULL;
	if (print)
		ft_perror("rrb\n");
}

void	rrr(t_node **a, t_node **b, bool print)
{
	rra(a, false);
	rrb(b, false);
	if (print)
		ft_perror("rrr\n");
}