/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:04:59 by slord             #+#    #+#             */
/*   Updated: 2022/04/26 14:13:16 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_element;

	n_element = malloc(sizeof(t_list));
	if (n_element == NULL)
		return (NULL);
	n_element->content = content;
	n_element->next = NULL;
	return (n_element);
}
