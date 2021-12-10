/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:43:44 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/05 13:31:38 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bfs_setup(t_system *sys)
{
	if (!(sys->arr = (int *)malloc(sizeof(int) * 3)))
		sys->err = 1;
	if (sys->n <= sys->chunk)
	{
		sys->arr[0] = sa;
		sys->arr[1] = ra;
		sys->arr[2] = rra;
	}
	else
	{
		sys->arr[0] = sb;
		sys->arr[1] = rb;
		sys->arr[2] = rrb;
	}
}

void	bfs_wrong_path(t_system *sys, t_optimizer *opt, int i)
{
	stack_instruction_rev(&sys->a, &sys->b, sys->arr[i]);
	stack_pop_del(opt->inst);
}

void	bfs_init(t_system *sys, int depth_curr, \
					int *depth_visited, t_optimizer *opt)
{
	int is_moved;
	int i;

	i = -1;
	while (++i < 3)
	{
		if (is_forbid_pattern(opt->inst))
			return ;
		if ((is_moved = stack_instruction(&sys->a, &sys->b, sys->arr[i])))
			stack_element(sys, opt->inst, sys->arr[i]);
		if (is_target(opt->target) && sys->optimal_cal > opt->inst->size)
		{
			sys->optimal_cal = opt->inst->size;
			optimize_inst_renew(sys, opt);
			stack_join(sys->opt->result, &sys->answer);
			return ;
		}
		else if (depth_curr < *depth_visited)
			bfs_init(sys, depth_curr + 1, depth_visited, opt);
		if (is_target(opt->target))
			return ;
		if (is_moved)
			bfs_wrong_path(sys, opt, i);
	}
	return ;
}

void	bfs_search(t_system *sys, int moved, t_stack *target)
{
	int i;
	int depth_visited;

	i = 0;
	depth_visited = 0;
	sys->optimal_cal = (moved) * (moved);
	bfs_setup(sys);
	sys->opt = optimize_init(sys, target);
	while (i < sys->optimal_cal)
	{
		bfs_init(sys, 0, &depth_visited, sys->opt);
		depth_visited++;
		i++;
		if (sys->opt->result->top)
			break ;
	}
	free_optimizer(sys->opt);
	sys->opt = NONE;
	free(sys->arr);
}
