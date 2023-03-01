/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:16:52 by bperron           #+#    #+#             */
/*   Updated: 2023/03/01 14:02:50 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	children(t_shell *shell, int i)
{
	change_in_and_out(shell, i);
	if (!check_output(shell, i))
		return ;
	if (!check_input(shell, i))
		return ;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_built_in(shell, i) == 0)
	{
		if (modify_command(shell, 0, NULL, NULL) == 0)
		{
			dprintf(2, "minishell: %s : command not found\n",
				shell->cmds_exe[0]);
			close_fds(shell);
			if (shell->path)
				free_pp((void *) shell->path);
			exit (127);
		}
		execve(shell->cmds_exe[0], shell->cmds_exe, shell->env);
	}
}

void	get_return_value(t_shell *shell)
{
	if (WIFEXITED(shell->status))
		shell->status = WEXITSTATUS(shell->status);
	else if (WIFSIGNALED(shell->status))
		shell->status = WTERMSIG(shell->status) + 128;
}

void	wait_child(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->id)
		while (shell->id[++i])
			waitpid(shell->id[i], &shell->status, 0);
	close_fds(shell);
	get_return_value(shell);
}

void	execute(t_shell *shell)
{
	int	i;

	i = 0;
	shell->terminal = 0;
	set_pipes(shell);
	while (i < shell->nb_cmds)
	{
		check_open_files(shell, i);
		if (shell->nb_cmds == 1)
			check_built_in_parent(shell, i);
		if (shell->terminal == 1)
			break ;
		check_heredoc_parent(shell, i);
		shell->id[i] = fork();
		if (shell->id[i] == 0)
		{
			children(shell, i);
			exit(1);
		}
		close(shell->fd[(i * 2) + 1]);
		if (i > 0)
			close(shell->fd[i * 2 - 2]);
		i++;
	}
	wait_child(shell);
}
