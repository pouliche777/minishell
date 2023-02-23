/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:51:42 by slord             #+#    #+#             */
/*   Updated: 2023/02/23 13:18:36 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	set_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->id = ft_calloc(shell->nb_cmds + 1, sizeof(int));
	shell->fd = ft_calloc(shell->nb_cmds * 2, sizeof(int));
	while (i < shell->nb_cmds)
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
	return (0);
}

void	change_in_and_out(t_shell *shell, int i)
{
	if (i)
		dup2(shell->fd[i * 2 - 2], STDIN_FILENO);
	if (i != shell->nb_cmds - 1)
		dup2(shell->fd[i * 2 + 1], STDOUT_FILENO);
}
