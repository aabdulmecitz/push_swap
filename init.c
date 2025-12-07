/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:29:31 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 15:41:40 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

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

void fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc)
{
    int i;
    t_node *new_node;
    t_node *tail;
    int value;

    i = 1;
    tail = NULL;
    while (argv[i])
    {
        if (!is_valid_int(argv[i]))
        {
            ft_perror("Error\n");
            if (gc)
                gc_free_all(gc);
            exit(1);
        }
        value = ft_atoi(argv[i]);
        new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
        if (!new_node)
        {
            ft_perror("Error\n");
            if (gc)
                gc_free_all(gc);
            exit(1);
        }
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = tail;
        if (tail)
            tail->next = new_node;
        else
            *temp_head = new_node;
        tail = new_node;
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
            ft_perror("Error\n");
            if (gc)
                gc_free_all(gc);
            exit(1);
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
    
    fill_temp_stack(stack_b, argv, gc);
    
    if (!check_values(*stack_b))
    {
        ft_perror("Error\n");
        if (gc)
            gc_free_all(gc);
        exit(1);
    }
    
    init_a_stack(stack_a, *stack_b, gc);
}