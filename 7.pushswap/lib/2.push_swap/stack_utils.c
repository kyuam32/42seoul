/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:06:12 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 12:08:20 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				stack_pop_del(t_stack *stack)
{
	t_element *temp;

	if (stack->top == NONE)
		return (0);
	temp = stack->top;
	if (stack->size == 1)
	{
		stack->top = NONE;
		stack->bot = NONE;
	}
	else
	{
		stack->top = temp->dw;
		stack->top->up = NONE;
	}
	temp->dw = NONE;
	temp->up = NONE;
	temp->num = 0;
	free(temp);
	stack->size--;
	return (1);
}

void			stack_join(t_stack *upper, t_stack *lower)
{
	t_element *lower_top;
	t_element *upper_bot;

	if (upper->top == NONE)
		return ;
	lower_top = lower->top;
	upper_bot = upper->bot;
	if (lower->top == NONE)
	{
		lower->top = upper->top;
		lower->bot = upper->bot;
	}
	else
	{
		lower_top->up = upper_bot;
		upper_bot->dw = lower_top;
		lower->top = upper->top;
	}
	lower->size += upper->size;
	upper->top = NONE;
	upper->bot = NONE;
	upper->size = 0;
}

t_stack			*copy_stack(t_system *sys, t_stack *ori)
{
	t_stack		*ret;
	t_element	*temp;

	if (!(ret = (t_stack *)malloc(sizeof(t_stack))))
		sys->err = 1;
	ft_memset(ret, 0, sizeof(t_stack));
	temp = ori->bot;
	while (temp)
	{
		stack_element(sys, ret, temp->num);
		temp = temp->up;
	}
	return (ret);
}

void			free_stack(t_stack *target)
{
	t_element *temp;

	if (target == 0)
		return ;
	temp = (target)->top;
	while (temp)
	{
		(target)->top = temp->dw;
		ft_memset(temp, 0, sizeof(t_element));
		free(temp);
		temp = (target)->top;
	}
	free(target);
}

int				stack_rev_element(t_stack *stk)
{
	t_element *temp;

	if (stk->top == NONE || stk->size == 1)
		return (0);
	temp = stk->bot;
	temp->up->dw = NONE;
	stk->bot = temp->up;
	stk->top->up = temp;
	temp->up = NONE;
	temp->dw = stk->top;
	stk->top = temp;
	return (1);
}
