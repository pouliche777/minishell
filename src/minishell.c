/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:39:06 by slord             #+#    #+#             */
/*   Updated: 2023/01/22 23:59:19 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->index-- > 0)
	{
		signals(1);
		check_dollar_in_command(shell, i, shell->cmds[i]);
		shell->id[i] = fork();
		if (shell->id[i] == 0)
		{
			if (!check_redirection(shell, i))
				return ;
			if (!check_input(shell, i))
				return ;
			supress_operators(shell, i);
			change_in_and_out(shell, i);
			if (check_built_in(shell, i) == 0)
			{
				modify_command(shell, i);
				execve(shell->cmds_exe[0], shell->cmds_exe, shell->env);
			}
			return ;
		}
		else
		{
			wait(&shell->status);
		}
		signals(3);
		close(shell->fd[(i * 2) + 1]);
		if (i > 0)
			close(shell->fd[i * 2 - 2]);
		i++;
		
	}
	launch_terminal(shell);
}

void	launch_terminal(t_shell *shell)
{
	shell->buffer = readline("~");
	lexer1(shell->buffer, shell);
	check_built_in_parent(shell);
	add_history(shell->buffer);
	printf("%s\n", shell->buffer);
	shell->index = shell->nb_cmds;
	set_pipes(shell);
	execute(shell);
	free(shell->buffer);
	free(shell->cmds);
	shell->cmds = NULL;
	shell->buffer = NULL;
}

void 	init_env(t_shell *shell, char **env)
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
	t_shell *shell;
	
	shell = get_struc();
	init_env(shell, env);
	get_path(shell);
	signals(0);
	//init_struc(&shell)
	launch_terminal(shell);
}

t_shell	*get_struc(void)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
		shell = malloc(sizeof(t_shell));
	return (shell);
}
