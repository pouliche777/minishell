/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:37:22 by slord             #+#    #+#             */
/*   Updated: 2022/04/11 19:38:44 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	source = src;
	destination = dest;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
