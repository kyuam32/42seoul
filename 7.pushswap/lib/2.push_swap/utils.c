/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:03:05 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 12:10:04 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		is_target(t_stack *target)
{
	t_element	*temp;
	int			pre;

	if (target->top == NONE)
		return (0);
	temp = target->top->dw;
	pre = target->top->num;
	while (temp)
	{
		if (pre > temp->num)
			return (0);
		pre = temp->num;
		temp = temp->dw;
	}
	return (1);
}

void	make_answer(t_system *sys, t_instruct inst)
{
	stack_instruction(&sys->a, &sys->b, inst);
	stack_element(sys, &sys->answer, inst);
}

void	print_error(void)
{
	write(1, "Error\n", 6);
	exit(-1);
}
