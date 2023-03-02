/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:39:06 by slord             #+#    #+#             */
/*   Updated: 2023/03/02 11:38:00 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

//signal dans heredoc qui fait du weird

void	free_garbage2(t_shell *shell, unsigned char status)
{
	close_fds(shell);
	free_env(shell);
	if (shell->cmds)
		free_arrarrarr(shell->cmds);
	free(shell);
	exit(status);
}

void	launch_terminal(t_shell *shell)
{
	while (1)
	{
		shell->error = 0;
		if (shell->buffer)
			free(shell->buffer);
		shell->buffer = NULL;
		signal_handling();
		shell->buffer = readline("MiniHell > ");
		if (shell->buffer == NULL)
		{
			free_garbage2(shell, shell->status);
		}
		if (ft_strlen(shell->buffer) > 0)
		{
			add_history(shell->buffer);
			signal(SIGQUIT, sighush);
			signal(SIGINT, sighush);
			lexer(shell->buffer, shell, 0, 0);
			if (shell->error == 0)
				execute(shell);
			shell->cmds = NULL;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	if (argc == 1 && argv[0])
	{
		shell = get_struc();
		init_env(shell, env);
		get_path(shell);
		launch_terminal(shell);
	}
}

t_shell	*get_struc(void)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
		shell = ft_calloc(sizeof(t_shell), 1);
	return (shell);
}
