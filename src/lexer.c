/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:57 by slord             #+#    #+#             */
/*   Updated: 2023/01/28 19:16:43 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (is_space(c))
		return (1);
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	next_quote(char *buffer, char c)
{
	int	i ;

	i = 0;
	while (buffer[i] != c)
		i++;
	return (i + 1);
}

void make_tree(char *cmd, int row, t_shell *shell)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;	
	k = 0;
	shell->cmds[row] = calloc(sizeof(char *), 10);
	while (is_space(cmd[i]))
		i++;
	k = i;
	if (cmd[i] == '>' || cmd[i] == '<')
	{
		if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
		{
			shell->cmds[row][j] = ft_substr(cmd, i, 2);
			i++;
			j++;
		}
		else
			shell->cmds[row][j] = ft_substr(cmd, i, 1);
		j++;
		while (is_space(cmd[i + 1]))
			i++;
		k = i + 1;
		i++;
	}
	while (1)
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i = i + next_quote(&cmd[i + 1], cmd[i]);
		}
		if (is_space(cmd[i]) || cmd[i] == '<' ||  cmd[i] == '>' || cmd[i]== '\0')
		{
			shell->cmds[row][j] = ft_substr(cmd, k, i - k);
			if (!cmd[i + 1])
				break ;
			j++;
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				i++;
			while (is_space(cmd[i]) && is_space(cmd[i + 1]))
			{
				i++;
				if (!cmd[i + 1] || cmd[i + 1] == '>' || cmd[i + 1] == '<')
					i++;
			}
			k = i + 1;
		}
		if (!cmd[i])
			break ;
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
			{
				shell->cmds[row][j] = ft_substr(cmd, i, 2);
				i++;
			}
			else
				shell->cmds[row][j] = ft_substr(cmd, i, 1);
			j++;
			while (is_space(cmd[i + 1]))
				i++;
			if (!cmd[i + 1])
				break ;
			k = i + 1;
		}
		i++;
	}
}

char	***lexer1(char *buffer, t_shell *shell)
{
	char	**pre_c;
	int		i;
	int		j;

	i = 0;
	count_cmds(shell);
	shell->id = malloc(sizeof(shell->nb_cmds * 4));
	j = shell->nb_cmds;
	shell->cmds = malloc(sizeof(char **) * j);
	pre_c = ft_split(buffer, '|');
	while (j > 0)
	{
		make_tree(pre_c[i], i, shell);
		i++;
		j--;
	}
	while (pre_c[j])
	{
		free(pre_c[j]);
		j++;
	}
	free(pre_c);
	return (shell->cmds);
}
