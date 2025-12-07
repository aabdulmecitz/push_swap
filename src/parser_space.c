/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:00:00 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:01:29 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*find_tail(t_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static void	extract_number(const char *str, int *i, char *num_str)
{
	int	num_idx;

	num_idx = 0;
	if ((str[*i] == '-' || str[*i] == '+') && 
		(str[*i + 1] >= '0' && str[*i + 1] <= '9'))
		num_str[num_idx++] = str[(*i)++];
	while (str[*i] >= '0' && str[*i] <= '9')
		num_str[num_idx++] = str[(*i)++];
	num_str[num_idx] = '\0';
}

static void	add_parsed_number(t_node **temp_head, const char *num_str, t_gc *gc)
{
	t_node	*new_node;
	t_node	*tail;

	if (!is_valid_int(num_str))
	{
		ft_perror("Error\n");
		gc_free_all(gc);
		exit(1);
	}
	new_node = (t_node *)gc_malloc(gc, sizeof(t_node));
	if (!new_node)
	{
		ft_perror("Error\n");
		gc_free_all(gc);
		exit(1);
	}
	new_node->value = ft_atoi(num_str);
	new_node->next = NULL;
	tail = find_tail(*temp_head);
	new_node->prev = tail;
	if (tail)
		tail->next = new_node;
	else
		*temp_head = new_node;
}

void	parse_space_separated(t_node **temp_head, const char *str, t_gc *gc)
{
	int		i;
	char	num_str[20];

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break;
		extract_number(str, &i, num_str);
		add_parsed_number(temp_head, num_str, gc);
	}
}
