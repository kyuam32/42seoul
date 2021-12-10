/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:23:23 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/06 13:53:51 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/2.push_swap/push_swap.h"

int	main(int argc, char **argv)
{
	t_system	sys;

	ft_memset(&sys, 0, sizeof(sys));
	if (argc < 2)
		exit(1);
	else if (!argument_is_valid(&sys, argc, argv))
		print_error();
	if (is_target(&sys.a))
		exit(1);
	sys.chunk = 7;
	if (sys.n <= sys.chunk)
		bfs_search(&sys, sys.chunk, &sys.a);
	else
	{
		merge_setup(&sys);
		divide(&sys);
		conquer(&sys);
	}
	if (sys.err)
		write(1, "malloc error\n", 13);
	stack_instruction_print(&sys.answer);
	exit(0);
}
