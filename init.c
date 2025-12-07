/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:29:31 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:39:16 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int check_value(t_temp_node *head)
{
    if (head->value )
    {
        /* code */
    }
       
    return 0;
}

void fill_temp_stack(t_temp_node **temp_head, char **argv, t_gc_node **gc)
{
    int i;
    t_temp_node *new_node;
    t_temp_node *tail;

    i = 1;
    tail = NULL;
    while (argv[i])
    {
        new_node = (t_temp_node *)gc_malloc(sizeof(t_temp_node));
        new_node->value = argv[i];
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

void init_stacks(t_node **stack_a, t_node **stack_b, char **argv)
{
    t_temp_node  *temp_head;
    
    *stack_a = NULL;
    *stack_b = NULL;
    
    
    
    
}