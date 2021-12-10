/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:04:00 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 11:48:23 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		stack_element(t_system *sys, t_stack *stk, int n)
{
	t_element *new;

	if (!(new = (t_element *)malloc(sizeof(t_element))))
		return (sys->err = 1);
	if (stk->top == NONE)
	{
		new->dw = NONE;
		stk->bot = new;
	}
	else
	{
		new->dw = stk->top;
		stk->top->up = new;
	}
	new->up = NONE;
	new->num = n;
	stk->top = new;
	stk->size++;
	return (0);
}

void	stack_push_element2(t_stack *to, t_element *temp)
{
	if (to->top == NONE)
	{
		to->top = temp;
		to->bot = temp;
		temp->dw = NONE;
	}
	else
	{
		temp->dw = to->top;
		to->top->up = temp;
		to->top = temp;
	}
	to->size++;
}

int		stack_push_element(t_stack *from, t_stack *to)
{
	t_element *temp;

	if (from->top == NONE)
		return (0);
	temp = from->top;
	if (from->size == 1)
	{
		from->top = NONE;
		from->bot = NONE;
	}
	else
	{
		from->top = temp->dw;
		temp->dw->up = NONE;
	}
	from->size--;
	stack_push_element2(to, temp);
	return (1);
}

int		stack_swap_element(t_stack *stk)
{
	int temp;

	if (stk->top == NONE || stk->size == 1)
		return (0);
	temp = stk->top->num;
	stk->top->num = stk->top->dw->num;
	stk->top->dw->num = temp;
	return (1);
}

int		stack_rot_element(t_stack *stk)
{
	t_element *temp;

	if (stk->top == NONE || stk->size == 1)
		return (0);
	temp = stk->top;
	stk->top = temp->dw;
	stk->top->up = NONE;
	stk->bot->dw = temp;
	temp->up = stk->bot;
	temp->dw = NONE;
	stk->bot = temp;
	return (1);
}
