/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:50:30 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 15:27:24 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_last(t_node *head)
{
    t_node	*current;

    if (!head)
        return (NULL);
    current = head;
    while (current->next)
        current = current->next;
    return (current);
}

void	print_stack_a(t_node *a)
{
	t_node	*current;
	char	buffer[20];
	int		i;
	int		num;
	int		temp;

	if (!a)
	{
		ft_perror("Stack A is empty\n");
		return ;
	}
	ft_perror("Stack A: ");
	current = a;
	while (current)
	{
		num = current->value;
		if (num < 0)
		{
			write(2, "-", 1);
			num = -num;
		}
		i = 0;
		temp = num;
		if (temp == 0)
		{
			write(2, "0", 1);
		}
		else
		{
			while (temp > 0)
			{
				buffer[i++] = (temp % 10) + '0';
				temp /= 10;
			}
			while (i > 0)
				write(2, &buffer[--i], 1);
		}
		if (current->next)
			write(2, " ", 1);
		current = current->next;
	}
	write(2, "\n", 1);
}

