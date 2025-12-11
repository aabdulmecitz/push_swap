#include "checker_bonus.h"
#include "../includes/push_swap.h"
#include "../lib/libft/libft.h"

static void	cleanup_gc(t_gc *gc)
{
	if (!gc)
		return ;
	gc_free_all(gc);
	free(gc);
}

int	print_check_result(t_node *stack_a, t_node *stack_b)
{
	if (stack_b || !is_sorted(stack_a))
	{
		ft_putstr_fd("KO\n", 1);
		return (0);
	}
	ft_putstr_fd("OK\n", 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	t_gc			*gc;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (0);
	gc = init_stacks(&stack_a, &stack_b, argv, NULL);
	if (!gc)
		return (1);
	if (!process_input(&stack_a, &stack_b, gc))
		return (cleanup_gc(gc), 1);
	print_check_result(stack_a, stack_b);
	cleanup_gc(gc);
	return (0);
}