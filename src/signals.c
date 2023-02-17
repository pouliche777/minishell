/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:46 by slord             #+#    #+#             */
/*   Updated: 2023/02/16 14:28:58 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

/* void	handler_sigusr(int signalnb)
{
	if (signalnb == SIGQUIT)
		(void) SIGQUIT;
	if (signalnb == SIGINT)
	{
		//launch_terminal();
		(void) SIGINT;
	}
}

void	sig_handler(int sig)
{
	t_shell	*shell;
	
	shell = get_struc();
	if (sig == SIGQUIT)
	{
		
		rl_on_new_line();
		rl_redisplay();
		
		sigignore(SIGQUIT);
	}
	if (sig == SIGINT)
	{	
		printf("\n");
		launch_terminal(shell);
	}
	
}

void	signals(int i)
{
	struct sigaction	sa_signal;

	sa_signal.sa_handler = 0;
	if (i == 0)
		sa_signal.sa_handler = sig_handler;
	else if (i == 1)
		sa_signal.sa_handler = handler_sigusr;
	else
		sa_signal.sa_handler = sig_handler;
	sigaction(SIGQUIT, &sa_signal, NULL);
	sigaction(SIGINT, &sa_signal, NULL);
	sigaction(SIGTERM, &sa_signal, NULL);
	sa_signal.sa_flags = SA_RESTART;
} */

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
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	launch_terminal(get_struc());
}

/* void	sigheredoc(int signum)
{
	(void) signum;
	free_heredoc2(&g_vars);
	exit(130);
} */

/* void	sigheredoc2(int signum)
{
	(void) signum;
	g_vars.exit = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
} */

void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandlerc);
}
