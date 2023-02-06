/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:11:43 by slord             #+#    #+#             */
/*   Updated: 2023/02/06 16:30:04 by slord            ###   ########.fr       */
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

void	redirect_output(char *cmd)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file[1] = dup2(file[0], STDOUT_FILENO);
	}
}

void	redirect_output_1(char *cmd)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open (cmd, O_CREAT | O_APPEND | O_WRONLY, 0777);
		file[1] = dup2(file[0], STDOUT_FILENO);
	}
}

void	redirect_input(char *cmd)
{
	int	file[2];

	if (cmd)
	{
		file[0] = open (cmd, O_RDONLY, 0777);
		dup2(file[0], STDIN_FILENO);
	}
}

int	check_output(t_shell *shell, int i)
{
	int		j;
	char	**cmd;

	cmd = shell->cmds[i];
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '>' && cmd[j][1] == '>' && cmd[j + 1] != NULL)
		{
			redirect_output_1(cmd[j + 1]);
			if (cmd[j + 1] == NULL)
				return (0);
		}
		else if (cmd[j][0] == '>' && cmd[j][1] == '\0' && cmd[j + 1] != NULL)
		{
			redirect_output(cmd[j + 1]);
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
			redirect_input(cmd[j + 1]);
		else if (cmd[j][0] == '<' && cmd[j][1] == '<' && cmd[j][2] == '\0')
		{
			dup2(shell->heredoc_fd[0], STDIN_FILENO);
			close(shell->heredoc_fd[1]);
		}	
		j++;
	}
	return (1);
}

void write_heredoc(char *input, int *file)
{
	ft_putstr_fd(input, file[1]);
	ft_putchar_fd('\n', file[1]);
}

void	heredoc(t_shell *shell, char *cmd)
{
	shell->heredoc_input = readline(">");
	if (pipe(shell->heredoc_fd) < 0)
		return ;
	while (shell->heredoc_input && ft_strcmp(shell->heredoc_input, cmd))
	{
		check_dollar_in_heredoc(shell);
		ft_putstr_fd(shell->heredoc_input, shell->heredoc_fd[1]);
		ft_putchar_fd('\n', shell->heredoc_fd[1]);
		free(shell->heredoc_input);
		shell->heredoc_input = readline(">");
	}
	close(shell->heredoc_fd[1]);
	free(shell->heredoc_input);
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

void	check_dollar_in_heredoc(t_shell *shell)
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
