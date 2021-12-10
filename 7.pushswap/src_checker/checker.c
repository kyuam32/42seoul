/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:06:38 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/06 13:30:31 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/2.push_swap/push_swap.h"

void	print_result(t_system *sys, t_stack *a, t_stack *b)
{
	if (is_target(a) && sys->a.size == a->size && b->size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int		instruction_is_valid(t_stack *a, t_stack *b, char *line)
{
	if (!ft_strcmp(line, "sa"))
		return (stack_instruction(a, b, sa));
	else if (!ft_strcmp(line, "sb"))
		return (stack_instruction(a, b, sb));
	else if (!ft_strcmp(line, "ss"))
		return (stack_instruction(a, b, ss));
	else if (!ft_strcmp(line, "pa"))
		return (stack_instruction(a, b, pa));
	else if (!ft_strcmp(line, "pb"))
		return (stack_instruction(a, b, pb));
	else if (!ft_strcmp(line, "ra"))
		return (stack_instruction(a, b, ra));
	else if (!ft_strcmp(line, "rb"))
		return (stack_instruction(a, b, rb));
	else if (!ft_strcmp(line, "rr"))
		return (stack_instruction(a, b, rr));
	else if (!ft_strcmp(line, "rra"))
		return (stack_instruction(a, b, rra));
	else if (!ft_strcmp(line, "rrb"))
		return (stack_instruction(a, b, rrb));
	else if (!ft_strcmp(line, "rrr"))
		return (stack_instruction(a, b, rrr));
	return (-1);
}

int		main(int argc, char **argv)
{
	t_system	sys;
	t_stack		*a;
	t_stack		*b;
	char		*line;

	ft_memset(&sys, 0, sizeof(sys));
	if (argc < 2)
		exit(-1);
	if (!argument_is_valid(&sys, argc, argv))
		print_error();
	sys.opt = optimize_init(&sys, 0);
	a = copy_stack(&sys, &sys.a);
	b = copy_stack(&sys, &sys.b);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (instruction_is_valid(a, b, line) == -1)
			print_error();
	}
	print_result(&sys, a, b);
	exit(0);
}
