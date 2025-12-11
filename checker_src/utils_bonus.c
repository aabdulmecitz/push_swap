#include "checker_bonus.h"
#include "../lib/libft/libft.h"

static void	exit_with_error(void)
{
	ft_perror("Error\n");
	exit(1);
}

void	process_the_input(char *input, t_node **stack_a, t_node **stack_b)
{
	if (ft_strncmp(input, "pa", 2) == 0)
		pa(stack_a, stack_b, true);
	else if (ft_strncmp(input, "pb", 2) == 0)
		pb(stack_b, stack_a, true);
	else if (ft_strncmp(input, "sa", 2) == 0)
		sa(stack_a, true);
	else if (ft_strncmp(input, "sb", 2) == 0)
		sb(stack_b, true);
	else if (ft_strncmp(input, "ss", 2) == 0)
		ss(stack_a, stack_b, true);
	else if (ft_strncmp(input, "rra", 3) == 0)
		rra(stack_a, true);
	else if (ft_strncmp(input, "rrb", 3) == 0)
		rrb(stack_b, true);
	else if (ft_strncmp(input, "rrr", 3) == 0)
		rrr(stack_a, stack_b, true);
	else if (ft_strncmp(input, "ra", 2) == 0)
		ra(stack_a, true);
	else if (ft_strncmp(input, "rb", 2) == 0)
		rb(stack_b, true);
	else if (ft_strncmp(input, "rr", 2) == 0)
		rr(stack_a, stack_b, true);
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