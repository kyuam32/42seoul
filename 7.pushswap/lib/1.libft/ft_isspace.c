/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:29:47 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/06 13:00:13 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((unsigned char)c == '\t')
		return (1);
	else if ((unsigned char)c == '\n')
		return (1);
	else if ((unsigned char)c == '\v')
		return (1);
	else if ((unsigned char)c == '\f')
		return (1);
	else if ((unsigned char)c == '\r')
		return (1);
	else if ((unsigned char)c == ' ')
		return (1);
	return (0);
}
