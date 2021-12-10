/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:15:29 by nlee              #+#    #+#             */
/*   Updated: 2020/11/02 21:00:09 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*terminate;

	if (lst == 0 || del == 0)
		return ;
	temp = *lst;
	while (temp)
	{
		terminate = temp;
		temp = temp->next;
		ft_lstdelone(terminate, del);
	}
	*lst = 0;
}
