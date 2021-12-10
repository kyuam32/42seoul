/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:49:56 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 11:53:07 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_instruction_print(t_stack *stack)
{
	t_element *temp;

	temp = stack->bot;
	while (temp)
	{
		stack_instruction_convert(temp->num);
		write(1, "\n", 1);
		temp = temp->up;
	}
}

void	stack_instruction_convert(int i)
{
	if (i == sa)
		write(1, "sa", 2);
	else if (i == sb)
		write(1, "sb", 2);
	else if (i == ss)
		write(1, "ss", 2);
	else if (i == pa)
		write(1, "pa", 2);
	else if (i == pb)
		write(1, "pb", 2);
	else if (i == ra)
		write(1, "ra", 2);
	else if (i == rb)
		write(1, "rb", 2);
	else if (i == rr)
		write(1, "rr", 2);
	else if (i == rra)
		write(1, "rra", 3);
	else if (i == rrb)
		write(1, "rrb", 3);
	else if (i == rrr)
		write(1, "rrr", 3);
}

int		is_forbid_pattern(t_stack *list)
{
	t_element *top;

	if (list->top == NONE)
		return (0);
	top = list->top;
	if (list->size > 1)
	{
		if (top->num == sa && top->dw->num == sa)
			return (1);
		else if (top->num == sb && top->dw->num == sb)
			return (1);
		else if (top->num == ra && top->dw->num == rra)
			return (1);
		else if (top->num == rb && top->dw->num == rrb)
			return (1);
		else if (top->num == rra && top->dw->num == ra)
			return (1);
		else if (top->num == rrb && top->dw->num == rb)
			return (1);
	}
	return (0);
}

int		stack_instruction(t_stack *a, t_stack *b, t_instruct inst)
{
	if (inst == sa)
		return (stack_swap_element(a));
	else if (inst == sb)
		return (stack_swap_element(b));
	else if (inst == ss)
		return (stack_swap_element(a) || stack_swap_element(b));
	else if (inst == pa)
		return (stack_push_element(b, a));
	else if (inst == pb)
		return (stack_push_element(a, b));
	else if (inst == ra)
		return (stack_rot_element(a));
	else if (inst == rb)
		return (stack_rot_element(b));
	else if (inst == rr)
		return (stack_rot_element(a) || stack_rot_element(b));
	else if (inst == rra)
		return (stack_rev_element(a));
	else if (inst == rrb)
		return (stack_rev_element(b));
	else if (inst == rrr)
		return (stack_rev_element(a) || stack_rev_element(b));
	return (-1);
}

int		stack_instruction_rev(t_stack *a, t_stack *b, t_instruct inst)
{
	if (inst == sa)
		return (stack_swap_element(a));
	else if (inst == sb)
		return (stack_swap_element(b));
	else if (inst == ss)
		return (stack_swap_element(a) || stack_swap_element(b));
	else if (inst == pa)
		return (stack_push_element(a, b));
	else if (inst == pb)
		return (stack_push_element(b, a));
	else if (inst == ra)
		return (stack_rev_element(a));
	else if (inst == rb)
		return (stack_rev_element(b));
	else if (inst == rr)
		return (stack_rev_element(a) || stack_rev_element(b));
	else if (inst == rra)
		return (stack_rot_element(a));
	else if (inst == rrb)
		return (stack_rot_element(b));
	else if (inst == rrr)
		return (stack_rot_element(a) || stack_rot_element(b));
	return (-1);
}
