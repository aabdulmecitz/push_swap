/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:29:31 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:27:48 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*create_node(int value, t_gc *gc)
{
	t_node	*new_node;

	new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static void	append_node(t_node **head, t_node *new_node)
{
	t_node	*tail;

	if (*head == NULL)
		*head = new_node;
	else
	{
		tail = *head;
		while (tail->next)
			tail = tail->next;
		tail->next = new_node;
		new_node->prev = tail;
	}
}

static int	parse_single_number(t_node **temp_head, const char *str, t_gc *gc)
{
	t_node	*new_node;

	if (!is_valid_int(str))
	{
		ft_perror("Error\n");
		return (0);
	}
	new_node = create_node(ft_atoi(str), gc);
	if (!new_node)
	{
		ft_perror("Error\n");
		return (0);
	}
	append_node(temp_head, new_node);
	return (1);
}

int	fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc)
{
	int	i;
	int	num_count;

	i = 1;
	while (argv[i])
	{
		num_count = count_numbers(argv[i]);
		if (num_count < 0)
		{
			ft_perror("Error\n");
			return (0);
		}
		if (num_count > 1 || ft_strlen(argv[i]) > 11)
		{
			if (!parse_space_separated(temp_head, argv[i], gc))
				return (0);
		}
		else
		{
			if (!parse_single_number(temp_head, argv[i], gc))
				return (0);
		}
		i++;
	}
	return (1);
}

int	init_a_stack(t_node **a, t_node *temp_head, t_gc *gc)
{
	t_node	*current;
	t_node	*new_node;
	t_node	*check;
	int		index;

	current = temp_head;
	while (current)
	{
		new_node = create_node(current->value, gc);
		if (!new_node)
		{
			ft_perror("Error\n");
			return (0);
		}
		index = 0;
		check = temp_head;
		while (check)
		{
			if (check->value < current->value)
				index++;
			check = check->next;
		}
		new_node->index = index;
		append_node(a, new_node);
		current = current->next;
	}
	return (1);
}

t_gc	*init_stacks(t_node **stack_a, t_node **stack_b, char **argv, t_gc *gc)
{
	t_gc	*local_gc;
	t_node	*temp_head;

	local_gc = NULL;
	if (!gc)
	{
		local_gc = (t_gc *)malloc(sizeof(t_gc));
		if (!local_gc)
		{
			ft_perror("Error\n");
			return (NULL);
		}
		gc_init(local_gc);
		gc = local_gc;
	}
	*stack_a = NULL;
	*stack_b = NULL;
	if (!argv || !argv[1])
	{
		ft_perror("Error\n");
		gc_free_all(gc);
		if (local_gc)
			free(local_gc);
		return (NULL);
	}
	temp_head = NULL;
	if (!fill_temp_stack(&temp_head, argv, gc))
	{
		gc_free_all(gc);
		if (local_gc)
			free(local_gc);
		return (NULL);
	}
	if (!check_values(temp_head))
	{
		ft_perror("Error\n");
		gc_free_all(gc);
		if (local_gc)
			free(local_gc);
		return (NULL);
	}
	if (!init_a_stack(stack_a, temp_head, gc))
	{
		gc_free_all(gc);
		if (local_gc)
			free(local_gc);
		return (NULL);
	}
	return (local_gc);
}
