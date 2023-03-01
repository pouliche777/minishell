/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:46 by slord             #+#    #+#             */
/*   Updated: 2023/03/01 11:30:41 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	sighandlerc(int signum)
{
	int	pid;

	pid = getpid();
	if (pid == 0)
		exit (0);
	else
	{
		if (signum == SIGINT)
		{
			get_struc()->status = 1;
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sighush(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
}

void	sigheredoc(int signum)
{
	t_shell	*shell;
	int		i;

	(void) signum;
	shell = get_struc();
	if (shell->heredoc_input)
		free(shell->heredoc_input);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	close_fds(shell);
	i = -1;
	if (shell->nb_cmds > 1)
		while (shell->id[++i])
			kill(shell->id[i], SIGKILL);
	launch_terminal(shell);
}

void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandlerc);
}
