/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:36:12 by bperron           #+#    #+#             */
/*   Updated: 2023/02/27 14:43:31 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

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

int	modify_command(t_shell *info, int j, char *str, char *ptr)
{
	if (access(info->cmds_exe[0], F_OK) == 0)
		return (1);
	get_path(info);
	ptr = ft_strjoin("/", info->cmds_exe[0]);
	while (info->path[j])
	{
		str = ft_strjoin(info->path[j], ptr);
		if (access(str, F_OK) == 0)
		{
			info->cmds_exe[0] = NULL;
			free(info->cmds_exe[0]);
			info->cmds_exe[0] = ft_calloc(2, ft_strlen(str));
			ft_strlcpy(info->cmds_exe[0], str, ft_strlen(str) + 1);
			free(str);
			free_pp((void *) info->path);
			return (1);
		}
		free(str);
		j++;
	}
	free_pp((void *) info->path);
	return (0);
}

void	supress_operators(t_shell *shell, int i)
{
	int	j;
	int	h;

	h = 0;
	j = 0;
	shell->cmds_exe = ft_calloc(sizeof(char *),
			(count_nb_tokens(shell->cmds[i])) + 1);
	while (shell->cmds[i][j])
	{
		if (shell->cmds[i][j][0] == '>' || shell->cmds[i][j][0] == '<')
			j = j + 2;
		else
		{
			shell->cmds_exe[h] = ft_strdup(shell->cmds[i][j]);
			h++;
			j++;
		}
	}
}
