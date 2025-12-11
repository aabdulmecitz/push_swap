/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:42:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 02:41:01 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_max(t_node *stack)
{
	t_node	*max_node;

	if (!stack)
		return (NULL);
	max_node = stack;
	while (stack)
	{
		if (stack->value > max_node->value)
			max_node = stack;
		stack = stack->next;
	}
	return (max_node);
}

void	sort_three(t_node **a)
{
	t_node	*max_node;

	max_node = find_max(*a);
	if (max_node == *a)
		ra(a, true);
	else if ((*a)->next == max_node)
		rra(a, true);
	if ((*a)->value > (*a)->next->value)
		sa(a, true);
}

static int	position_of_index(t_node *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

static int	list_size(t_node *stack)
{
	int	len;

	len = 0;
	while (stack)
	{
		len++;
		stack = stack->next;
	}
	return (len);
}

static void	mark_lis_nodes(t_node *stack)
{
	int		len;
	int		i;
	int		j;
	int		best_len;
	int		best_idx;
	int		indices[1024];
	int		dp[1024];
	int		prev[1024];
	t_node	*cur;

	len = list_size(stack);
	if (len <= 1)
		return ;
	cur = stack;
	i = 0;
	while (cur && i < 1024)
	{
		indices[i] = cur->index;
		cur = cur->next;
		i++;
	}
	len = i;
	i = 0;
	while (i < len)
	{
		dp[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (indices[j] < indices[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
	best_len = 0;
	best_idx = 0;
	i = 0;
	while (i < len)
	{
		if (dp[i] > best_len)
		{
			best_len = dp[i];
			best_idx = i;
		}
		i++;
	}
	bool	keep_flags[1024] = {0};
	while (best_idx != -1)
	{
		keep_flags[best_idx] = true;
		best_idx = prev[best_idx];
	}
	cur = stack;
	i = 0;
	while (cur && i < len)
	{
		cur->keep = keep_flags[i] ? 1 : 0;
		cur = cur->next;
		i++;
	}
}

static void	push_non_keep(t_node **a, t_node **b)
{
	int		len;
	int		i;

	len = get_stack_size(*a);
	i = 0;
	while (i < len)
	{
		if ((*a)->keep == 0)
			pb(a, b, true);
		else
			ra(a, true);
		i++;
	}
}

static int	find_target_position(t_node *stack_a, int b_index)
{
	t_node	*current;
	int		pos;
	int		best_pos;
	int		best_index;
	int		min_index;
	int		min_pos;

	current = stack_a;
	pos = 0;
	best_pos = -1;
	best_index = INT_MAX;
	min_index = INT_MAX;
	min_pos = 0;
	while (current)
	{
		if (current->index < min_index)
		{
			min_index = current->index;
			min_pos = pos;
		}
		if (current->index > b_index && current->index < best_index)
		{
			best_index = current->index;
			best_pos = pos;
		}
		current = current->next;
		pos++;
	}
	if (best_pos != -1)
		return (best_pos);
	return (min_pos);
}

static int	calculate_rotation_cost(int position, int stack_size)
{
	if (stack_size == 0)
		return (0);
	if (position <= stack_size / 2)
		return (position);
	return (stack_size - position);
}

static int	get_rotation_direction(int position, int stack_size)
{
	if (stack_size == 0)
		return (1);
	if (position <= stack_size / 2)
		return (1);
	return (-1);
}

static t_cost	calculate_cost(int target_pos_a, int pos_b, int size_a,
		int size_b)
{
	t_cost	cost;

	cost.cost_a = calculate_rotation_cost(target_pos_a, size_a);
	cost.cost_b = calculate_rotation_cost(pos_b, size_b);
	cost.direction_a = get_rotation_direction(target_pos_a, size_a);
	cost.direction_b = get_rotation_direction(pos_b, size_b);
	if (cost.direction_a == cost.direction_b)
		cost.total_cost = (cost.cost_a > cost.cost_b) ? cost.cost_a
			: cost.cost_b;
	else
		cost.total_cost = cost.cost_a + cost.cost_b;
	return (cost);
}

static void	apply_rotation(t_node **stack_a, t_node **stack_b, t_cost cost)
{
	while (cost.direction_a == 1 && cost.direction_b == 1
		&& cost.cost_a > 0 && cost.cost_b > 0)
	{
		rr(stack_a, stack_b, true);
		cost.cost_a--;
		cost.cost_b--;
	}
	while (cost.direction_a == -1 && cost.direction_b == -1
		&& cost.cost_a > 0 && cost.cost_b > 0)
	{
		rrr(stack_a, stack_b, true);
		cost.cost_a--;
		cost.cost_b--;
	}
	while (cost.cost_a-- > 0)
	{
		if (cost.direction_a == 1)
			ra(stack_a, true);
		else
			rra(stack_a, true);
	}
	while (cost.cost_b-- > 0)
	{
		if (cost.direction_b == 1)
			rb(stack_b, true);
		else
			rrb(stack_b, true);
	}
}

static void	align_smallest_to_top(t_node **stack_a)
{
	int	size_a;
	int	pos_min;

	size_a = get_stack_size(*stack_a);
	pos_min = position_of_index(*stack_a, 1);
	if (pos_min == -1)
		return ;
	if (pos_min <= size_a / 2)
	{
		while (pos_min-- > 0)
			ra(stack_a, true);
	}
	else
	{
		pos_min = size_a - pos_min;
		while (pos_min-- > 0)
			rra(stack_a, true);
	}
}

static t_target	find_cheapest_target(t_node *stack_a, t_node *stack_b)
{
	t_target	best;
	t_target	current_target;
	t_node		*current_b;
	int			size_a;
	int			size_b;
	int			pos_b;
	int			best_cost;

	size_a = get_stack_size(stack_a);
	size_b = get_stack_size(stack_b);
	current_b = stack_b;
	pos_b = 0;
	best_cost = INT_MAX;
	best.index = -1;
	while (current_b)
	{
		current_target.index = current_b->index;
		current_target.target_pos_a = find_target_position(stack_a,
				current_b->index);
		current_target.target_pos_b = pos_b;
		current_target.move_cost = calculate_cost(current_target.target_pos_a,
				pos_b, size_a, size_b);
		if (current_target.move_cost.total_cost < best_cost)
		{
			best_cost = current_target.move_cost.total_cost;
			best = current_target;
		}
		current_b = current_b->next;
		pos_b++;
	}
	return (best);
}

static void	move_best_from_b(t_node **stack_a, t_node **stack_b)
{
	t_target	best;
	t_node		*current;
	int			pos_b;

	best = find_cheapest_target(*stack_a, *stack_b);
	if (best.index == -1)
		return ;
	current = *stack_b;
	pos_b = 0;
	while (current && current->index != best.index)
	{
		current = current->next;
		pos_b++;
	}
	if (!current)
		return ;
	best.target_pos_b = pos_b;
	best.move_cost = calculate_cost(best.target_pos_a, pos_b,
			get_stack_size(*stack_a), get_stack_size(*stack_b));
	apply_rotation(stack_a, stack_b, best.move_cost);
	pa(stack_a, stack_b, true);
}

void	sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	(void)gc;
	if (is_sorted(*stack_a))
		return ;
	if (get_stack_size(*stack_a) <= 3)
		return (sort_three(stack_a));
	mark_lis_nodes(*stack_a);
	push_non_keep(stack_a, stack_b);
	if (get_stack_size(*stack_a) == 2 && !is_sorted(*stack_a))
		sa(stack_a, true);
	else if (get_stack_size(*stack_a) >= 3)
		sort_three(stack_a);
	while (*stack_b)
		move_best_from_b(stack_a, stack_b);
	align_smallest_to_top(stack_a);
}
    