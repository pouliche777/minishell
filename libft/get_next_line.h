/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:16:49 by slord             #+#    #+#             */
/*   Updated: 2022/07/12 14:56:32 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>

char	*get_next_line(int fd);
int		ft_search_n(char *str);
char	*ft_strjoin1(char *s1, char *s2, int char_read);
size_t	ft_strlen1(const char *str);
void	*ft_calloc1(size_t count, size_t size);
void	ft_bzero1(void *ptr, size_t n);

#endif
