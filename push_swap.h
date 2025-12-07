/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:37:23 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_temp_node
{
    char                *value;
    struct s_temp_node  *next;
    struct s_temp_node  *prev;
}               t_temp_node;

typedef struct s_node
{
    int             value;
    struct s_node   *next;
    struct s_node   *prev;
}               t_node;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc
{
	t_gc_node			*head;
	int					count;
}						t_gc;


#endif