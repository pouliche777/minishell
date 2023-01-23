/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:57 by slord             #+#    #+#             */
/*   Updated: 2023/01/20 18:37:39 by slord            ###   ########.fr       */
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

char ***lexer(char *buffer)
{
	char	***cmds;
	int		i;
	int		k;
	int		ii;
	int		jj;

	i = 0;
	k = 0;
	ii = 0;
	jj = 0;
	cmds = malloc(sizeof(char **) * 10);
	cmds[0] = malloc(sizeof(char *) * 10);
	while (1)
	{
		if (buffer[i] == '\'' || buffer[i] == '\"')
		{
			i = i + next_quote(&buffer[i + 1], buffer[i]);
		}
		if (is_separator(buffer[i]))
		{
			cmds[ii][jj] = ft_substr(buffer, k, i - k);
			jj++;
			if (buffer[i] == '>' || buffer[i] == '<')
			{
				if (buffer[i + 1] == '>' || buffer[i + 1] == '<')
				{
					cmds[ii][jj] = ft_substr(buffer, i, 2);
					i++;
				}
				else
					cmds[ii][jj] = ft_substr(buffer, i, 1);
				jj++;
			}	
			if (buffer[i] == '|')
			{
				ii++;
				cmds[ii] = malloc(sizeof(char *) * 10);
				jj = 0;
				while (is_separator(buffer[i + 1]))
					i++;
			}
			k = i + 1;
		}
		if (buffer[i] == '\0')
		{
			if (!is_separator(buffer[i - 1]))
				cmds[ii][jj] = ft_substr(buffer, k, i - k);
			break ;
		}
		while (is_space(buffer[i]))
			i++;
		i++;
	}
	return (cmds);
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
				//j++;
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

char ***lexer1(char *buffer, t_shell *shell)
{
	char**	pre_c;
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
	while(pre_c[j])
	{
		free(pre_c[j]);
		j++;
	}
	free(pre_c);
	return (shell->cmds);
}
