/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:43:56 by slord             #+#    #+#             */
/*   Updated: 2023/02/09 10:28:08 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_inset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	end;

	if (s1 == 0 || set == 0)
		return (NULL);
	while (s1 && char_inset(*s1, set))
	{
		s1++;
	}
	end = ft_strlen(s1) - 1;
	while (char_inset(s1[end], set) && end > 0)
	{
		end--;
	}
	return (ft_substr(s1, 0, (size_t)end + 1));
}
