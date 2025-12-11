/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:43:27 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/08 01:02:43 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_perror(const char *msg)
{
	const char	*text;

	text = msg;
	if (!text)
		text = "Error\n";
	while (*text)
		write(1, text++, 1);
}
