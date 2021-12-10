/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:54:57 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 11:05:39 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_element	*merge_units(t_element *top, t_element *mid)
{
	t_element *result;

	result = NONE;
	if (top == NONE)
		return (mid);
	else if (mid == NONE)
		return (top);
	if (top->num < mid->num)
	{
		result = top;
		result->dw = merge_units(top->dw, mid);
	}
	else
	{
		result = mid;
		result->dw = merge_units(top, mid->dw);
	}
	return (result);
}

void		merge_split_list(t_element **top, t_element **mid)
{
	t_element *slow;
	t_element *fast;

	slow = *top;
	fast = (*top)->dw;
	while (fast != NONE)
	{
		fast = fast->dw;
		if (fast != NONE)
		{
			fast = fast->dw;
			slow = slow->dw;
		}
	}
	*mid = slow->dw;
	(*mid)->up = NONE;
	slow->dw = NONE;
}

void		merge_sort(t_element **top_ref)
{
	t_element *top;
	t_element *mid;

	top = *top_ref;
	if (top == NONE || top->dw == NONE)
		return ;
	merge_split_list(&top, &mid);
	merge_sort(&top);
	merge_sort(&mid);
	*top_ref = merge_units(top, mid);
}

void		merge_setup(t_system *sys)
{
	t_element *temp1;
	t_element *temp2;

	sys->sorted = copy_stack(sys, &sys->a);
	merge_sort(&sys->sorted->top);
	if (sys->sorted->size > 1)
	{
		temp1 = sys->sorted->top;
		temp2 = sys->sorted->top->dw;
		while (temp2)
		{
			temp2->up = temp1;
			temp1 = temp1->dw;
			temp2 = temp2->dw;
		}
	}
}
