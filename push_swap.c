/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:27 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 15:27:24 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_node  *stack_a;
    t_node  *stack_b;

    (void)argc;
    init_stacks(&stack_a, &stack_b, argv, NULL);
    print_stack_a(stack_a);
    
    return 0;
}