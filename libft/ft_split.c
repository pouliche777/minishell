/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:03:52 by slord             #+#    #+#             */
/*   Updated: 2022/04/25 19:13:55 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (*str == c)
			j = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**ptr;
	unsigned int	i;
	int				h;
	int				words;

	if (!s)
		return (NULL);
	ptr = ft_calloc(sizeof(char *), (ft_countwords(s, c) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	h = -1;
	words = ft_countwords(s, c);
	while (++h < words)
	{
		while (s[0] == c)
			s++;
		while (s[i] != c && s[i] != '\0')
			i++;
		ptr[h] = ft_substr(s, 0, i);
		s = s + ft_strlen(ptr[h]);
		i = 0;
	}
	ptr[h] = NULL;
	return (ptr);
}
