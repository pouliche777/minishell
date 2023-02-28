/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:29 by bperron           #+#    #+#             */
/*   Updated: 2023/02/28 15:32:20 by slord            ###   ########.fr       */
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
}

void	free_garbage(t_shell *shell, unsigned char status)
{
	free_env(shell);
	if (shell->cmds)
		free_arrarrarr(shell->cmds);
	(void) shell;
	exit(status);
}

void	close_fds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmds * 2)
	{
		close(shell->fd[i]);
		i++;
	}
}

void	check_open_files(t_shell *shell, int i)
{
	char	**cmd;
	int		j;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '>' && cmd[j][1] == '>' && cmd[j + 1] != NULL)
		{
			open(cmd[j + 1], O_WRONLY | O_CREAT, 0777);
		}
		else if (cmd[j][0] == '>' && cmd[j][1] == '\0' && cmd[j + 1] != NULL)
		{
			open(cmd[j + 1], O_WRONLY | O_CREAT, 0777);
		}
		j++;
	}
}