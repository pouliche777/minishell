/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:36:12 by bperron           #+#    #+#             */
/*   Updated: 2023/03/01 11:33:13 by bperron          ###   ########.fr       */
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

int	is_dir(char *file)
{
	struct stat	path;

	if (access(file, F_OK) == -1)
		return (1);
	stat(file, &path);
	if (S_ISREG(path.st_mode) == 0)
		dprintf(2, "minishell: %s : is a directory\n", file);
	return (S_ISREG(path.st_mode));
}

int	modify_command(t_shell *info, int j, char *str, char *ptr)
{
	if (is_dir(info->cmds_exe[0]) == 0)
		return (0);
	if ((access(info->cmds_exe[0], F_OK) == 0))
		return (1);
	get_path(info);
	ptr = ft_strjoin("/", info->cmds_exe[0]);
	while (info->path[j])
	{
		str = ft_strjoin(info->path[j++], ptr);
		if (access(str, F_OK) == 0)
		{
			free(info->cmds_exe[0]);
			info->cmds_exe[0] = ft_calloc(sizeof(char), ft_strlen(str) + 1);
			ft_strlcpy(info->cmds_exe[0], str, ft_strlen(str) + 1);
			free(str);
			free_pp((void *) info->path);
			return (1);
		}
		free(str);
	}
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
