/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:57:09 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/04 11:07:11 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		free_optimizer(t_optimizer *target)
{
	if (target == 0)
		return ;
	free_stack(target->inst);
	free_stack(target->result);
	target->inst = 0;
	target->result = 0;
	target->target = 0;
	free(target);
}

t_optimizer	*optimize_init(t_system *sys, t_stack *target)
{
	t_optimizer *opt;

	if (!(opt = (t_optimizer *)malloc(sizeof(t_optimizer))))
		sys->err = 1;
	opt->target = target;
	if (!(opt->inst = (t_stack *)malloc(sizeof(t_stack))))
		sys->err = 1;
	ft_memset(opt->inst, 0, sizeof(t_stack));
	if (!(opt->result = (t_stack *)malloc(sizeof(t_stack))))
		sys->err = 1;
	ft_memset(opt->result, 0, sizeof(t_stack));
	return (opt);
}

void		optimize_inst_renew(t_system *sys, t_optimizer *curr)
{
	t_stack *temp;

	temp = sys->opt->result;
	sys->opt->result = copy_stack(sys, curr->inst);
	if (temp != NONE)
		free_stack(temp);
}
