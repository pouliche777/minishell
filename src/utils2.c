/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:29 by bperron           #+#    #+#             */
/*   Updated: 2023/03/02 10:58:14 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arrarrarr(char ***arr)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
			free(arr[i][j]);
		free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

void	free_garbage(t_shell *shell, unsigned char status)
{
	close_fds(shell);
	free_env(shell);
	if (shell->cmds_exe)
	{
		free_pp((void *) shell->cmds_exe);
		shell->cmds_exe = NULL;
	}
	if (shell->cmds)
		free_arrarrarr(shell->cmds);
	free(shell);
	exit(status);
}

void	close_fds(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->fd)
	{
		while (++i < shell->nb_cmds * 2)
			close(shell->fd[i]);
		free(shell->fd);
		shell->fd = NULL;
	}
	if (shell->id)
	{
		free(shell->id);
		shell->id = NULL;
	}
}

void	check_open_files(t_shell *shell, int i)
{
	char	**cmd;
	int		j;
	int		fd;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '>' && cmd[j][1] == '>' && cmd[j + 1] != NULL)
		{
			fd = open(cmd[j + 1], O_WRONLY | O_CREAT, 0777);
			close (fd);
		}
		else if (cmd[j][0] == '>' && cmd[j][1] == '\0' && cmd[j + 1] != NULL)
		{
			fd = open(cmd[j + 1], O_WRONLY | O_CREAT, 0777);
			close (fd);
		}
		j++;
	}
}
