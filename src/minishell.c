/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:39:06 by slord             #+#    #+#             */
/*   Updated: 2023/02/24 08:30:52 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	launch_terminal(t_shell *shell)
{
	while (1)
	{
		if (shell->buffer)
			free(shell->buffer);
		shell->buffer = NULL;
		signal_handling();
		shell->buffer = readline("MiniHell > ");
		if (shell->buffer == NULL)
			exit(shell->status);
		if (ft_strlen(shell->buffer) > 0)
		{
			add_history(shell->buffer);
			signal(SIGQUIT, sighush);
			signal(SIGINT, sighush);
			lexer(shell->buffer, shell);
			set_pipes(shell);
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
