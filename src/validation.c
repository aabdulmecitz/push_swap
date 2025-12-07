/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:00:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:01:29 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_int(const char *str)
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
		return (0);
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

static int	check_duplicates(t_node *head)
{
	t_node	*current;
	t_node	*check;

	current = head;
	while (current)
	{
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

int	check_values(t_node *head)
{
	t_node	*current;

	if (!head)
		return (0);
	current = head;
	while (current)
	{
		if (current->value < INT_MIN || current->value > INT_MAX)
			return (0);
		current = current->next;
	}
	return (check_duplicates(head));
}
