/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:49:50 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 15:57:30 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void parse_space_separated(t_node **temp_head, const char *str, t_gc *gc)
{
	int		i;
	char	num_str[20];
	int		num_idx;
	t_node	*new_node;
	t_node	*tail;
	int		value;

	i = 0;
	tail = NULL;
	if (*temp_head != NULL)
	{
		tail = *temp_head;
		while (tail->next)
			tail = tail->next;
	}
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break;
		num_idx = 0;
		if ((str[i] == '-' || str[i] == '+') && 
			(str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			num_str[num_idx++] = str[i++];
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			num_str[num_idx++] = str[i++];
		}
		num_str[num_idx] = '\0';
		if (!is_valid_int(num_str))
		{
			ft_perror("Error\n");
			if (gc)
				gc_free_all(gc);
			exit(1);
		}
		value = ft_atoi(num_str);
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
	}
}