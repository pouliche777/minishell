/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:05 by slord             #+#    #+#             */
/*   Updated: 2022/04/22 20:19:10 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen((char *)s))
	{
		ptr = ft_calloc(len + 1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	else
	{
		ptr = ft_calloc(len + 1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		ft_strlcpy(ptr, s + start, len + 1);
		return (ptr);
	}
}
