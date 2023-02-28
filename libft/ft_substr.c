/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:05 by slord             #+#    #+#             */
/*   Updated: 2023/02/28 09:22:16 by bperron          ###   ########.fr       */
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
		ptr = ft_calloc(len + 2, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		ft_strlcpy(ptr, s + start, len + 1);
		return (ptr);
	}
}
