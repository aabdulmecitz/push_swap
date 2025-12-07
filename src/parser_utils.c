/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:00:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:04:48 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sign_at_start(const char *str, int i)
{
	return ((str[i] == '-' || str[i] == '+') && 
			(i == 0 || (str[i - 1] == ' ' || str[i - 1] == '\t')));
}

static int	is_digit_or_sign(const char *str, int i)
{
	return ((str[i] >= '0' && str[i] <= '9') || is_sign_at_start(str, i));
}

int	count_numbers(const char *str)
{
	int	count;
	int	in_number;
	int	i;

	count = 0;
	in_number = 0;
	i = 0;
	while (str[i])
	{
		if (is_digit_or_sign(str, i))
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
