/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:18:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/12/11 11:11:18 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	int				keep;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_cost
{
	int			cost_a;
	int			cost_b;
	int			total_cost;
	int			direction_a;
	int			direction_b;
}	t_cost;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node		*head;
	int				count;
}	t_gc;

typedef struct s_target
{
	int			index;
	int			target_pos_a;
	int			target_pos_b;
	t_cost		move_cost;
}	t_target;

int				is_valid_int(const char *str);
int				check_values(t_node *head);
int				count_numbers(const char *str);
int				ft_atoi(const char *str);
int				parse_space_separated(t_node **temp_head,\
				const char *str, t_gc *gc);
t_gc			*init_stacks(t_node **stack_a, t_node **stack_b,\
				char **argv, t_gc *gc);
int				fill_temp_stack(t_node **temp_head, char **argv, t_gc *gc);
int				init_a_stack(t_node **a, t_node *temp_head, t_gc *gc);
void			gc_init(t_gc *gc);
void			gc_add(t_gc *gc, void *ptr);
void			*gc_malloc(t_gc *gc, size_t size);
char			*gc_strdup(t_gc *gc, const char *str);
void			gc_remove(t_gc *gc, void *ptr);
void			gc_free_all(t_gc *gc);
void			gc_add_string_array(t_gc *gc, char **array);
t_node			*create_node(int value, t_gc *gc);
void			append_node(t_node **head, t_node *new_node);
t_node			*find_last(t_node *head);
void			ft_perror(const char *msg);
void			sa(t_node **a, bool print);
void			sb(t_node **b, bool print);
void			ss(t_node **a, t_node **b, bool print);
void			pa(t_node **a, t_node **b, bool print);
void			pb(t_node **a, t_node **b, bool print);
void			ra(t_node **a, bool print);
void			rb(t_node **b, bool print);
void			rr(t_node **a, t_node **b, bool print);
void			rra(t_node **a, bool print);
void			rrb(t_node **b, bool print);
void			rrr(t_node **a, t_node **b, bool print);
int				get_position(t_node *stack, int value);
int				get_stack_size(t_node *stack);
void			move_to_b(t_node **stack_a, t_node **stack_b);
void			sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc);
void			sort_three(t_node **a);
bool			is_sorted(t_node *a);
void			mark_lis_nodes(t_node *stack);
int				position_of_index(t_node *stack, int index);
int				find_target_position(t_node *stack_a, int b_index);
t_cost			calculate_cost(int target_pos_a, int pos_b,\
				int size_a, int size_b);
void			apply_rotation(t_node **stack_a, t_node **stack_b, t_cost cost);
void			align_smallest_to_top(t_node **stack_a);
t_target		find_cheapest_target(t_node *stack_a, t_node *stack_b);
void			move_best_from_b(t_node **stack_a, t_node **stack_b);

#endif