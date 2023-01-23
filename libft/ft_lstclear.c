/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:58:46 by slord             #+#    #+#             */
/*   Updated: 2022/04/26 13:49:11 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tempo;

	if (!del)
		return ;
	if (!*lst)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		tempo = *lst;
		*lst = (*lst)->next;
		free(tempo);
	}
	*lst = NULL;
}
