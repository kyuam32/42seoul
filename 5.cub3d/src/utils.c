/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:54:33 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 14:49:34 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(void *target)
{
	if (target != NULL)
		free(target);
	target = NULL;
}

void	print_ptr(char **s)
{
	int i;

	i = -1;
	while (s[++i] != NULL)
		printf("|%s|\n", s[i]);
}

void	v_iput(t_vector *vec, int x_input, int y_input)
{
	vec->x = (double)x_input;
	vec->y = (double)y_input;
}

void	v_dput(t_vector *vec, double x_input, double y_input)
{
	vec->x = x_input;
	vec->y = y_input;
}

int		skip_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
