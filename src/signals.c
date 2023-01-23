/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:46 by slord             #+#    #+#             */
/*   Updated: 2022/11/28 02:04:38 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handler_sigusr(int signalnb)
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
	if (sig == SIGQUIT)
	{
		sigignore(SIGQUIT);
	}
	if (sig == SIGINT)
	{	
		t_shell *shell;
		
		shell = get_struc();
		if (shell->buffer)
			free(shell->buffer);
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
}
