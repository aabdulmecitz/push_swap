/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:43:27 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 14:43:39 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_perror(const char *msg)
{
    if (msg)
    {
        while (*msg)
            write(2, msg++, 1);
    }
    else
    {
        const char *default_msg = "Error\n";
        while (*default_msg)
            write(2, default_msg++, 1);
    }
}