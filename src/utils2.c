/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:29 by bperron           #+#    #+#             */
/*   Updated: 2023/02/27 11:21:50 by slord            ###   ########.fr       */
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
	j = -1;
	while (arr[++i])
	{
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
