#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdbool.h>
# include "../includes/push_swap.h"

int	process_input(t_node **stack_a, t_node **stack_b, t_gc *gc);
int	validate_and_apply(const char *line, t_node **stack_a,\
			t_node **stack_b);
int	print_check_result(t_node *stack_a, t_node *stack_b);

#endif