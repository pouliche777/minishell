/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:31:33 by slord             #+#    #+#             */
/*   Updated: 2023/02/23 13:39:05 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	separate_input(t_shell *info)
{
	int	i;

	i = 0;
	info->nb_cmds = 1;
	while (info->buffer[i])
	{
		if (info->buffer[i] == '|')
			info->nb_cmds++;
		i++;
	}
	info->pre_command = ft_split(info->buffer, '|');
}

void	separate_cmds(t_shell *info)
{
	int	i;

	i = 0;
	info->cmds = ft_calloc(sizeof(char **), info->nb_cmds);
	while (info->pre_command[i])
	{
		info->cmds[i] = ft_split(info->pre_command[i], ' ');
		i++;
	}
}

int	skip_quote(char *buffer, char c, t_shell *info)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			return (i);
		i++;
	}
	printf("MiniHell: parse error near '\\%c'\n", c);
	launch_terminal(info);
	return (0);
}

void	count_cmds(t_shell *info)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	info->nb_cmds = 1;
	while (info->buffer[i])
	{
		if (info->buffer[i] == '\'')
		{
			j = skip_quote(info->buffer + 1 + i, '\'', info);
			i = i + j + 1;
		}
		if (info->buffer[i] == '\"')
		{
			j = skip_quote(info->buffer + 1 + i, '\"', info);
			i = i + j + 1;
		}
		if (info->buffer[i] == '|')
			info->nb_cmds++;
		i++;
	}
}
