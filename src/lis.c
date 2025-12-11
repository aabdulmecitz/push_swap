/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:08:47 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:08:49 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	copy_indices(t_node *stack, int *arr)
{
	int	len;

	len = 0;
	while (stack && len < 1024)
	{
		arr[len] = stack->index;
		stack = stack->next;
		len++;
	}
	return (len);
}

static int	lis_dp(int *idx, int *dp, int *prev, int len)
{
	int	i;
	int	j;
	int	best;

	i = 0;
	best = 0;
	while (i < len)
	{
		dp[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (idx[j] < idx[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		if (dp[i] > dp[best])
			best = i;
		i++;
	}
	return (best);
}

static void	backtrack_keep(t_node *stack, int *prev, int len, int best)
{
	int		flags[1024];
	int		pos;
	t_node	*cur;

	pos = 0;
	while (pos < len)
		flags[pos++] = 0;
	while (best != -1)
	{
		flags[best] = 1;
		best = prev[best];
	}
	cur = stack;
	pos = 0;
	while (cur && pos < len)
	{
		cur->keep = flags[pos];
		cur = cur->next;
		pos++;
	}
}

void	mark_lis_nodes(t_node *stack)
{
	int	idx[1024];
	int	dp[1024];
	int	prev[1024];
	int	len;
	int	best;

	if (!stack)
		return ;
	len = copy_indices(stack, idx);
	best = lis_dp(idx, dp, prev, len);
	backtrack_keep(stack, prev, len, best);
}
