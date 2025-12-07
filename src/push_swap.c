/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:27 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:24:17 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_node  *stack_a;
    t_node  *stack_b;
    t_gc    *gc;

    (void)argc;
    gc = init_stacks(&stack_a, &stack_b, argv, NULL);
    if (!gc)
        return (1);
    print_stack_a(stack_a);
    if (gc)
    {
        gc_free_all(gc);
        free(gc);
    }
    return (0);
}