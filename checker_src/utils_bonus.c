#include "checker_bonus.h"
#include "../lib/libft/libft.h"

static void	exit_with_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static int	match_op(const char *input, const char *op)
{
	size_t	len;

	len = ft_strlen(op);
	return (ft_strncmp(input, op, len) == 0
		&& (input[len] == '\n' || input[len] == '\0'));
}

void	process_the_input(char *input, t_node **stack_a, t_node **stack_b)
{
	if (match_op(input, "pa"))
		pa(stack_a, stack_b, false);
	else if (match_op(input, "pb"))
		pb(stack_b, stack_a, false);
	else if (match_op(input, "sa"))
		sa(stack_a, false);
	else if (match_op(input, "sb"))
		sb(stack_b, false);
	else if (match_op(input, "ss"))
		ss(stack_a, stack_b, false);
	else if (match_op(input, "rra"))
		rra(stack_a, false);
	else if (match_op(input, "rrb"))
		rrb(stack_b, false);
	else if (match_op(input, "rrr"))
		rrr(stack_a, stack_b, false);
	else if (match_op(input, "ra"))
		ra(stack_a, false);
	else if (match_op(input, "rb"))
		rb(stack_b, false);
	else if (match_op(input, "rr"))
		rr(stack_a, stack_b, false);
	else
		exit_with_error();
}

int	validate_and_apply(const char *line, t_node **stack_a,
			t_node **stack_b)
{
	if (!line || !stack_a || !stack_b)
		return (0);
	process_the_input((char *)line, stack_a, stack_b);
	return (1);
}

int	process_input(t_node **stack_a, t_node **stack_b, t_gc *gc)
{
	char	*line;

	if (!stack_a || !stack_b || !gc)
		return (0);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		gc_add(gc, line);
		if (!validate_and_apply(line, stack_a, stack_b))
			return (0);
		line = get_next_line(STDIN_FILENO);
	}
	return (1);
}
