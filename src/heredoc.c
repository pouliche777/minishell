/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:50:22 by slord             #+#    #+#             */
/*   Updated: 2023/02/27 11:39:56 by bperron          ###   ########.fr       */
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
		while (cmd[++i + 1] )
			hold[++j] = cmd[i];
		return (hold);
	}
	else
		shell->marde = 1;
	return (cmd);
}

void	heredoc(t_shell *shell, char *cmd)
{
	char *delim;

	delim = is_quote(cmd, shell);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigheredoc);
	shell->heredoc_input = NULL;
	shell->heredoc_input = readline(">");
	if (pipe(shell->heredoc_fd) < 0)
		return ;
	while (shell->heredoc_input && ft_strcmp(shell->heredoc_input, delim))
	{
		if (shell->marde)
			check_dollar_in_heredoc(shell);
		ft_putstr_fd(shell->heredoc_input, shell->heredoc_fd[1]);
		ft_putchar_fd('\n', shell->heredoc_fd[1]);
		free(shell->heredoc_input);
		shell->heredoc_input = NULL;
		shell->heredoc_input = readline(">");
	}
	close(shell->heredoc_fd[1]);
	rl_replace_line("", 0);
	free(shell->heredoc_input);
}

void	heredoc_variable(t_shell *shell, int j)
{
	char	*temp;
	int		i;
	int		h;
	char	*var;

	temp = ft_strdup(shell->heredoc_input);
	free(shell->heredoc_input);
	h = j + 1;
	while (temp[h] != '\0' && temp[h] != ' ')
		h++;
	var = ft_substr(temp, j + 1, h);
	i = -1;
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
			heredoc_variable(shell, j);
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
