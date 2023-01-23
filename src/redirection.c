/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:11:43 by slord             #+#    #+#             */
/*   Updated: 2023/01/23 01:28:43 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//fonction qui verifie si on doit changer le output ou le input du process

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
			redirect_output_1(shell, cmd[j + 1], i);
		else if (cmd[j][0] == '>' && cmd[j][1] == '\0')
			redirect_output(shell, cmd[j + 1], i);
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

	if (pipe(file) < 0)
		return ;
	shell->heredoc_input = readline(">");
	while (ft_strncmp(shell->heredoc_input, cmd, ft_strlen(shell->heredoc_input)))
	{
		ft_putstr_fd(shell->heredoc_input, file[1]);
		ft_putchar_fd('\n', file[1]);
		free(shell->heredoc_input);
		shell->heredoc_input = readline(">");
	}

	dup2(file[0], STDIN_FILENO);
	close(file[1]);
}

void	heredoc_variable(t_shell *shell)
{
	char	*temp;
	int		i;

	i = -1;
	while (shell->heredoc_input[++i])
	{
		if (shell->heredoc_input[i] == '$' && shell->heredoc_input[i + 1])
		{
			change_heredoc_input(shell,shell->heredoc_input+i+1, i);
			i = -1;
		}
			
	}

}

void	change_heredoc_input(t_shell *shell, char *input, int i;)
{
	char *temp;
	int j;
	int h;	
	h=0;
	j = 0;
	while(shell->env[j])
	{
		if (!(ft_strncmp(input, shell->env[j], ft_strlen(input))) && shell->env[j][ft_strlen(input)] == '=')
			break ;
		j++;
		if (!(shell->env[j]))
			return ;
	}
	free (shell->heredoc_input);
	while (h < i)
	{
		shell->heredoc_input[h] = input[h];
		h++;
	}
	check_env_heredoc(&shell->heredoc_input[i])
	temp = ft_strdup(shell->heredoc_input);
	free(shell->heredoc_input);
	
		j++;
	
}