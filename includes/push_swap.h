/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/07 16:01:29 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

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

int					is_valid_int(const char *str);
int					check_values(t_node *head);
int					count_numbers(const char *str);
int					ft_strlen(const char *s);
int					ft_atoi(const char *str);
void				parse_space_separated(t_node **temp_head, const char *str, t_gc *gc);
t_gc				*init_stacks(t_node **stack_a, t_node **stack_b, char **argv, t_gc *gc);
void				fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc);
void				init_a_stack(t_node **a, t_node *temp_head, t_gc *gc);

void				gc_init(t_gc *gc);
void				gc_add(t_gc *gc, void *ptr);
void				*gc_malloc(t_gc *gc, size_t size);
char				*gc_strdup(t_gc *gc, const char *str);
void				gc_remove(t_gc *gc, void *ptr);
void				gc_free_all(t_gc *gc);
void				gc_add_string_array(t_gc *gc, char **array);

t_node				*find_last(t_node *head);
void				ft_perror(const char *msg);
void				print_stack_a(t_node *a);

void				sa(t_node **a, bool print);
void				sb(t_node **b, bool print);
void				ss(t_node **a, t_node **b, bool print);

void				pa(t_node **a, t_node **b, bool print);
void				pb(t_node **a, t_node **b, bool print);

void				ra(t_node **a, bool print);
void				rb(t_node **b, bool print);
void				rr(t_node **a, t_node **b, bool print);

void				rra(t_node **a, bool print);
void				rrb(t_node **b, bool print);
void				rrr(t_node **a, t_node **b, bool print);

#endif