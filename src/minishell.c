/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:39:06 by slord             #+#    #+#             */
/*   Updated: 2023/01/29 00:09:09 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmds)
	{
		signals(1);
		check_quotes(shell, i, 0);
		check_dollar_in_command(shell, i, shell->cmds[i]);
		shell->id[i] = fork();
		if (shell->id[i] == 0)
		{
			change_in_and_out(shell, i);
			if (!check_redirection(shell, i))
				return ;
			if (!check_input(shell, i))
				return ;
			supress_operators(shell, i);
			if (check_built_in(shell, i) == 0)
			{
				modify_command(shell, i);
				execve(shell->cmds_exe[0], shell->cmds_exe, shell->env);
			}
			return ;
		}

		signals(3);
		close(shell->fd[(i * 2) + 1]);
		if (i > 0)
			close(shell->fd[i * 2 - 2]);
		i++;
	}
	i = -1;
	
	while (shell->id[++i])
		waitpid(shell->id[i], &shell->status, 0);
	launch_terminal(shell);
}

void	launch_terminal(t_shell *shell)
{
	shell->buffer = readline("~");
	if (shell->buffer == NULL)
		launch_terminal(shell);
	lexer1(shell->buffer, shell);
	add_history(shell->buffer);
	printf("%s\n", shell->buffer);
	shell->index = shell->nb_cmds;
	set_pipes(shell);
	check_built_in_parent(shell);
	execute(shell);
}

void	init_env(t_shell *shell, char **env)
{
	int		j;

	j = 0;
	while (env[j])
		j++;
	j--;
	shell->env = malloc(sizeof(char *) * (j + 1));
	shell->env[j + 1] = NULL;
	while (j >= 0)
	{
		shell->env[j] = ft_strdup(env[j]);
		j--;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	shell = get_struc();
	init_env(shell, env);
	get_path(shell);
	signals(0);
	launch_terminal(shell);
}

t_shell	*get_struc(void)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
		shell = malloc(sizeof(t_shell));
	return (shell);
}
