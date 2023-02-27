/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tardig <tardig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:16:00 by slord             #+#    #+#             */
/*   Updated: 2023/02/25 16:24:43 by tardig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2, int char_read)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = ft_calloc1(ft_strlen1(s1) + ft_strlen1(s2) + 1, sizeof(char));
	if (!ptr)
	{
		free (s1);
		return (NULL);
	}
	while (s1 != NULL && s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] && char_read-- > 0)
	{
		ptr[i++] = s2[j++];
	}
	free (s1);
	return (ptr);
}

int	ft_search_n(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

void	ft_bzero1(void *ptr, size_t n)
{
	int				i;

	i = 0;
	while (n-- > 0)
		((char *) ptr)[i++] = 0;
}

void	*ft_calloc1(size_t count, size_t size)
{
	
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero1(ptr, count * size);
	return ((void *) ptr);
}
