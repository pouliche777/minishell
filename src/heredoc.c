/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:50:22 by slord             #+#    #+#             */
/*   Updated: 2023/03/02 13:01:04 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*is_quote(char *cmd, t_shell *shell)
{
	char	*hold;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (cmd[0] == '\'' || cmd[0] == '"')
	{
		shell->marde = 0;
		hold = ft_calloc(sizeof(char), ft_strlen(cmd) - 1);
		while (cmd[++i + 1])
			hold[++j] = cmd[i];
		return (hold);
	}
	else
		shell->marde = 1;
	return (cmd);
}

void	heredoc(t_shell *shell, char *cmd)
{
	char	*delim;
	pid_t	pid;

	delim = is_quote(cmd, shell);
	shell->heredoc = 1;
	if (pipe(shell->heredoc_fd) < 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigheredoc);
		signal(SIGQUIT, SIG_IGN);
		shell->heredoc_input = NULL;
		shell->heredoc_input = readline(">");
		heredoc_1(shell, delim);
		free(shell->heredoc_input);
		exit (0);
	}
	waitpid(pid, &shell->status, 0);
	close(shell->heredoc_fd[1]);
	rl_replace_line("", 0);
}

void	heredoc_variable(t_shell *shell, int j, int h, int i)
{
	char	*temp;
	char	*var;

	temp = ft_strdup(shell->heredoc_input);
	free(shell->heredoc_input);
	while (temp[h] != '\0' && temp[h] != ' '
		&& temp[h] != '\'' && temp[h] != '"')
		h++;
	var = ft_substr(temp, j + 1, h - j - 1);
	shell->heredoc_input = ft_calloc(1, ft_strlen(temp) + check_v(shell, var));
	while (temp[++i] != '$')
		shell->heredoc_input[i] = temp[i];
	if (shell->variable)
	{
		ft_strcpy(&shell->heredoc_input[i], shell->variable);
		i = ft_strlen(shell->variable) + i;
		free(shell->variable);
		shell->variable = NULL;
	}
	ft_strcpy(&shell->heredoc_input[i], &temp[h]);
	free (temp);
	free (var);
}

void	check_dollar_in_heredoc(t_shell *shell)
{
	int	j;

	j = 0;
	while (shell->heredoc_input[j])
	{
		if (shell->heredoc_input[j] == '$' && shell->heredoc_input[j + 1]
			&& shell->heredoc_input[j + 1] != ' ')
		{
			heredoc_variable(shell, j, j + 1, -1);
			j = -1;
		}
		j++;
	}
}

void	check_heredoc_parent(t_shell *shell, int i)
{
	int		j;
	char	**cmd;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '<' && cmd[j][1] == '<' && cmd[j][2] == '\0')
			(heredoc(shell, cmd[j + 1]));
		j++;
	}
}
