/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:26:34 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:49:01 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **a, bool print)
{
	int	temp;

	if (!*a || !(*a)->next)
		return ;
	temp = (*a)->value;
	(*a)->value = (*a)->next->value;
	(*a)->next->value = temp;
	if (print)
		ft_perror("sa\n");
}

void	sb(t_node **b, bool print)
{
	int	temp;

	if (!*b || !(*b)->next)
		return ;
	temp = (*b)->value;
	(*b)->value = (*b)->next->value;
	(*b)->next->value = temp;
	if (print)
		ft_perror("sb\n");
}

void	ss(t_node **a, t_node **b, bool print)
{
	sa(a, false);
	sb(b, false);
	if (print)
		ft_perror("ss\n");
}