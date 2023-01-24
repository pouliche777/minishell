/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:31:33 by slord             #+#    #+#             */
/*   Updated: 2023/01/23 20:33:59 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	info->cmds = malloc(sizeof(char **) * info->nb_cmds);
	while (info->pre_command[i])
	{
		info->cmds[i] = ft_split(info->pre_command[i], ' ');
		i++;
	}
}

int	count_nb_tokens(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	duplicate_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->cmds_exe = malloc(sizeof(char **) * 10 + 1);
	while (shell->cmds[i]!= NULL)
	{
		shell->cmds_exe[i]  = malloc(count_nb_tokens(shell->cmds[i])
				* sizeof(char *));
		while (shell->cmds[i][j] != NULL)
		{
			if (shell->cmds[i][j][0] == '>' || shell->cmds[i][j][0] == '<')
			{
				shell->cmds_exe[i][j] = NULL;
				break ;
			}
			shell->cmds_exe[i][j] = ft_strdup(shell->cmds[i][j]);
			j++;
		}
		i++;
		j = 0;
	}
}

void	modify_command(t_shell *info, int i)
{
	int		j;
	char	*str;
	char	*ptr;

	j = 0;
	ptr = ft_strjoin("/", info->cmds_exe[0]);
	while (info->path[j])
	{
		str = ft_strjoin(info->path[j], ptr);
		if (access(str, F_OK) == 0)
		{
			info->cmds_exe[0] = NULL;
			info->cmds_exe[0] = realloc(info->cmds_exe[0], sizeof(str));
			ft_strlcpy(info->cmds_exe[0], str, ft_strlen(str) + 1);
		}
		free(str);
		j++;
	}
}

void	supress_operators(t_shell *shell, int i)
{
	int	j;
	int	h;

	h = 0;
	j = 0;
	shell->cmds_exe = calloc(sizeof(char *), 10);
	while (shell->cmds[i][j])
	{
		if (shell->cmds[i][j][0] == '>' || shell->cmds[i][j][0] == '<')
		{
			if (shell->cmds[i][j][0] == '>')
				break ;
			if (shell->cmds[i][j][0] == '<')
				break ;
			j = j + 2;
		}
		else
		{
			shell->cmds_exe[h] = ft_strdup(shell->cmds[i][j]);
			h++;
			j++;
		}
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
	printf("Invalid command\n");
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
