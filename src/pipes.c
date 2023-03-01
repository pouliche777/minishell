/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:51:42 by slord             #+#    #+#             */
/*   Updated: 2023/03/01 10:55:21 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	set_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->id = ft_calloc(shell->nb_cmds + 1, sizeof(int));
	if (shell->nb_cmds > 1)
	{
		shell->fd = ft_calloc(shell->nb_cmds - 1 * 2, sizeof(int));
		while (i < shell->nb_cmds - 1)
		{
			if (pipe(shell->fd + i * 2) == -1)
			{
				perror("Error: ");
				while (i >= 0)
				{
					close (shell->fd[i * 2]);
					close(shell->fd[i * 2 + 1]);
					i--;
				}
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	change_in_and_out(t_shell *shell, int i)
{
	if (i)
		dup2(shell->fd[i * 2 - 2], STDIN_FILENO);
	if (i != shell->nb_cmds - 1)
		dup2(shell->fd[i * 2 + 1], STDOUT_FILENO);
	close_fds(shell);
}
