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

static int	skip_sign(const char *str, int *sign)
{
	if (str[0] == '-')
	{
		*sign = -1;
		return (1);
	}
	if (str[0] == '+')
		return (-1);
	return (0);
}

static int	check_digits(const char *str, int i, int sign)
{
	long	num;

	num = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX)
			|| (sign == -1 && num > (long)INT_MAX + 1))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_int(const char *str)
{
	int	sign;
	int	i;

	if (!str || !*str)
		return (0);
	sign = 1;
	i = skip_sign(str, &sign);
	if (i < 0 || !str[i])
		return (0);
	return (check_digits(str, i, sign));
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
