/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:31:21 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/03 12:16:13 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	argument_is_duple(t_system *sys, int num)
{
	t_element *check;

	check = sys->a.top;
	while (check != NONE)
	{
		if (check->num == num)
			return (1);
		check = check->dw;
	}
	return (0);
}

int	argument_is_digit(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (i == 0 && (av[i] == '-' || av[i] == '+'))
			i++;
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (i);
}

int	argument_is_valid(t_system *sys, int ac, char **av)
{
	int	num;
	int is_in_range;

	num = 0;
	while (--ac > 0)
	{
		if (!argument_is_digit(av[ac]))
			return (0);
		if (!(is_in_range = ft_atoi2(av[ac], &num, 0, 1)))
			return (0);
		if (argument_is_duple(sys, num))
			return (0);
		stack_element(sys, &sys->a, num);
	}
	sys->n = sys->a.size;
	return (1);
}
