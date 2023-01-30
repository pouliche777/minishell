/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:11:43 by slord             #+#    #+#             */
/*   Updated: 2023/01/30 16:56:13 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//fonction qui verifie si on doit changer le output ou le input du process

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	redirect_output(t_shell *shell, char *cmd, int i)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file[1] = dup2(file[0], STDOUT_FILENO);
	}
}

void	redirect_output_1(t_shell *shell, char *cmd, int i)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open (cmd, O_CREAT | O_APPEND | O_WRONLY, 0777);
		file[1] = dup2(file[0], STDOUT_FILENO);
	}
}

void	redirect_input(t_shell *shell, char *cmd, int i)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open (cmd, O_RDONLY, 0777);
		dup2(file[0], STDIN_FILENO);
	}
}

int	check_redirection(t_shell *shell, int i)
{
	int		j;
	char	**cmd;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '>' && cmd[j][1] == '>' && cmd[j + 2] == NULL)
		{
			redirect_output_1(shell, cmd[j + 1], i);
			if (cmd[j + 1] == NULL)
				return (0);
		}
		else if (cmd[j][0] == '>' && cmd[j][1] == '\0')
		{
			redirect_output(shell, cmd[j + 1], i);
			if (cmd[j + 1] == NULL)
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_input(t_shell *shell, int i)
{
	int		j;
	char	**cmd;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '<' && cmd[j][1] == '\0')
			redirect_input(shell, cmd[j + 1], i);
		else if (cmd[j][0] == '<' && cmd[j][1] == '<' && cmd[j][2] == '\0')
			heredoc(shell, cmd[j + 1], i);
		j++;
	}
	return (1);
}

void write_heredoc(char *input, int *file)
{
	ft_putstr_fd(input, file[1]);
	ft_putchar_fd('\n', file[1]);
}

void	heredoc(t_shell *shell, char *cmd, int i)
{
	int		file[2];

	shell->heredoc_input = readline(">");
	if (pipe(file) < 0)
		return ;
	while (shell->heredoc_input && ft_strcmp(shell->heredoc_input, cmd))
	{
		check_dollar_in_heredoc(shell, shell->heredoc_input);
		ft_putstr_fd(shell->heredoc_input, file[1]);
		ft_putchar_fd('\n', file[1]);
		free(shell->heredoc_input);
		shell->heredoc_input = readline(">");
	}
	dup2(file[0], STDIN_FILENO);
	close(file[1]);
}

void	heredoc_variable(t_shell *shell, int j)
{
	char	*temp;
	int		i;
	int		h;
	char 	*var;

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

void	check_dollar_in_heredoc(t_shell *shell, char *heredoc)
{
	int	j;

	j = 0;
	while (shell->heredoc_input[j])
	{
		if (shell->heredoc_input[j] == '$' && shell->heredoc_input[j + 1] &&
			shell->heredoc_input[j + 1] != ' ')
		{
			heredoc_variable(shell, j);
			j = -1;
		}
		j++;
	}
}
