/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:11:13 by slord             #+#    #+#             */
/*   Updated: 2022/04/26 14:23:59 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new_list;
	t_list	*tempo;

	ptr = lst;
	new_list = NULL;
	while (ptr)
	{
		tempo = ft_lstnew((*f)(ptr->content));
		if (!tempo)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tempo);
		ptr = ptr->next;
	}
	return (new_list);
}
