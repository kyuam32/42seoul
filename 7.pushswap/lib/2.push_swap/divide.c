/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:14:48 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/05 17:53:43 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		devide_set_pivot(t_system *sys, int *p1, int *p2, int *moved)
{
	t_element	*temp;
	int			i;
	int			max;
	int			mid;

	temp = sys->sorted->top;
	max = sys->a.size - sys->a.size / 10 * 8;
	mid = sys->a.size - sys->a.size / 10 * 9;
	i = -1;
	while (++i < *moved)
		temp = temp->dw;
	i = 0;
	while (i < max)
	{
		if (i == mid)
			*p1 = temp->num;
		i++;
		if (!temp->dw)
			break ;
		temp = temp->dw;
	}
	*p2 = temp->num;
	return (i);
}

void	devide_push(t_system *sys, int *pvt1, int *pvt2, int moved)
{
	t_element *temp;

	temp = sys->a.top;
	while (sys->b.size != moved)
	{
		if (*pvt1 == *pvt2)
			make_answer(sys, pb);
		else
		{
			if (temp->num > *pvt2)
				make_answer(sys, ra);
			else
			{
				make_answer(sys, pb);
				if (temp->num <= *pvt1)
				{
					if (temp->dw != NONE)
						make_answer(sys, rb);
				}
			}
		}
		temp = sys->a.top;
	}
}

int		conquer_is_backward(t_system *sys, t_element *target)
{
	t_element	*temp;
	int			i;

	temp = sys->b.top;
	i = 0;
	if (!target)
		return (0);
	while (temp->num != target->num)
	{
		temp = temp->dw;
		i++;
	}
	if (i <= sys->b.size / 2)
		return (0);
	return (1);
}

void	conquer(t_system *sys)
{
	t_element	*temp;
	int			i;

	temp = sys->sorted->top;
	i = -1;
	while (++i < sys->sorted->size - 1)
		temp = temp->dw;
	while (sys->b.size != 0)
	{
		if (!conquer_is_backward(sys, temp))
		{
			while (sys->b.top->num != temp->num)
				make_answer(sys, rb);
			make_answer(sys, pa);
		}
		else
		{
			while (sys->b.top->num != temp->num)
				make_answer(sys, rrb);
			make_answer(sys, pa);
		}
		temp = temp->up;
	}
}

void	divide(t_system *sys)
{
	int pvt1;
	int pvt2;
	int moved;

	moved = 0;
	while (sys->a.size != 0)
	{
		moved += devide_set_pivot(sys, &pvt1, &pvt2, &moved);
		devide_push(sys, &pvt1, &pvt2, moved);
	}
}
