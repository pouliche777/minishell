/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:46 by slord             #+#    #+#             */
/*   Updated: 2023/03/02 11:36:43 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	sighandlerc(int signum)
{
	(void) signum;
	get_struc()->status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighush(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	
	return ;
}
void	sighush2(int signum)
{
	(void) signum;
	printf("ilhblihblhib\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit (130);
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
	rl_on_new_line();
	rl_replace_line("", 0);
	i = -1;
	close(shell->heredoc_fd[1]);
	close(shell->heredoc_fd[0]);
//	while (++i < shell->nb_cmds)
//	kill(shell->id[i], SIGINT);
	close_fds(shell);
	exit(130);
}

void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandlerc);
}
