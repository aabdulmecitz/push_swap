/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:29:31 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 15:57:19 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_valid_int(const char *str)
{
	long	num;
	int		sign;
	int		i;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		return (0);
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if (sign == 1 && num > INT_MAX)
			return (0);
		if (sign == -1 && num > (long)INT_MAX + 1)
			return (0);
		i++;
	}
	return (1);
}

int check_values(t_node *head)
{
	t_node	*current;
	t_node	*check;

	if (!head)
		return (0);
	current = head;
	while (current)
	{
		if (current->value < INT_MIN || current->value > INT_MAX)
			return (0);
		check = current->next;
		while (check)
		{
			if (current->value == check->value)
				return (0);
			check = check->next;
		}
		current = current->next;
	}
	return (1);
}

int count_numbers(const char *str)
{
	int	count;
	int	in_number;
	int	i;

	count = 0;
	in_number = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || 
			((str[i] == '-' || str[i] == '+') && 
			 (i == 0 || (str[i - 1] == ' ' || str[i - 1] == '\t'))))
		{
			if (!in_number)
			{
				count++;
				in_number = 1;
			}
		}
		else if (str[i] == ' ' || str[i] == '\t')
			in_number = 0;
		else
			return (-1);
		i++;
	}
	return (count);
}

void fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc)
{
	int		i;
	int		num_count;
	t_node	*new_node;
	t_node	*tail;

	i = 1;
	while (argv[i])
	{
		num_count = count_numbers(argv[i]);
		if (num_count < 0)
		{
			if (gc)
				gc_free_all(gc);
			(ft_perror("Error\n"), exit(1));
		}
		if (num_count > 1 || ft_strlen(argv[i]) > 11)
			parse_space_separated(temp_head, argv[i], gc);
		else
		{
			if (!is_valid_int(argv[i]))
			{
                if (gc)
                    gc_free_all(gc);
				(ft_perror("Error\n"), exit(1));
			}
			new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
			if (!new_node)
			{
				ft_perror("Error\n");
				if (gc)
					gc_free_all(gc);
				exit(1);
			}
			new_node->value = ft_atoi(argv[i]);
			new_node->next = NULL;
			new_node->prev = NULL;
			if (*temp_head == NULL)
			{
				*temp_head = new_node;
			}
			else
			{
				tail = *temp_head;
				while (tail->next)
					tail = tail->next;
				tail->next = new_node;
				new_node->prev = tail;
			}
		}
		i++;
	}
}

void init_a_stack(t_node **a, t_node *temp_head, t_gc *gc)
{
    t_node *current;
    t_node *new_node;
    t_node *tail;

    current = temp_head;
    tail = NULL;
    while (current)
    {
        new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
        if (!new_node)
        {
            if (gc)
                gc_free_all(gc);
            (ft_perror("Error\n"), exit(1));
        }
        new_node->value = current->value;
        new_node->next = NULL;
        new_node->prev = tail;
        if (tail)
            tail->next = new_node;
        else
            *a = new_node;
        tail = new_node;
        current = current->next;
    }
}

void init_stacks(t_node **stack_a, t_node **stack_b, char **argv, t_gc *gc)
{
    t_gc local_gc;
    t_node *temp_head;

    if (!gc)
    {
        gc_init(&local_gc);
        gc = &local_gc;
    }
    *stack_a = NULL;
    *stack_b = NULL;
    
    if (!argv || !argv[1])
    {
        ft_perror("Error\n");
        if (gc)
            gc_free_all(gc);
        exit(1);
    }
    
    temp_head = NULL;
    fill_temp_stack(&temp_head, argv, gc);
    
    if (!check_values(temp_head))
    {
        ft_perror("Error\n");
        if (gc)
            gc_free_all(gc);
        exit(1);
    }
    
    init_a_stack(stack_a, temp_head, gc);
}
