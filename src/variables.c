/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:17:48 by slord             #+#    #+#             */
/*   Updated: 2023/01/29 02:37:06 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	check_if_variable_exist(t_shell *shell, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (!(ft_strncmp(var, shell->env[i], ft_strlen(var)))
			&& shell->env[i][ft_strlen(var)] == '=')
		{
			shell->variable = ft_strdup(&shell->env[i][ft_strlen(var) + 1]);
			return ;
		}
		i++;
	}
}

void	replace_variable(t_shell *shell, int i, int j)
{
	int		h;
	char	*temp;

	h = 0;
	temp = ft_strdup(shell->cmds[i][j]);
	free(shell->cmds[i][j]);
	shell->cmds[i][j] = NULL;
	while (temp[h] != '$')
		h++;
	check_if_variable_exist(shell, &temp[h + 1]);
	shell->cmds[i][j] = calloc(1, 1000 + h + 1);
	h = 0;
	while (temp[h] != '$' && temp[h])
	{
		shell->cmds[i][j][h] = temp[h];
		h++;
	}
	if (shell->variable)
	{
		ft_strcpy(&shell->cmds[i][j][h], shell->variable);
		free (shell->variable);
	}
	else
		shell->cmds[i][j][h] = '\0';
	free(temp);
}
void	replace_variable_questionmark(t_shell *shell, int i, int j)
{
	int		h;
	char	*temp;

	h = 0;
	temp = ft_strdup(shell->cmds[i][j]);
	free(shell->cmds[i][j]);
	shell->cmds[i][j] = NULL;
	while (temp[h] != '$')
		h++;
	shell->cmds[i][j] = calloc(1, 1000 + h + 1);
	h = 0;
	while (temp[h] != '$' && temp[h])
	{
		shell->cmds[i][j][h] = temp[h];
		h++;
	}
	ft_strcpy(&shell->cmds[i][j][h], ft_itoa(shell->status));
	free(temp);
}
void	check_dollar_in_command(t_shell *shell, int i, char **cmd)
{
	int	j;
	int	h;

	j = 0;
	h = 0;
	while (cmd[j])
	{
		while (cmd[j][h])
		{
			if (cmd[j][h] == '$' && cmd[j][h + 1])
			{
				if (cmd[j][h + 1] == '?' && cmd[j][h + 2] == '\0')
					replace_variable_questionmark(shell, i, j);
				else
					replace_variable(shell, i, j);
				break ;
			}
			h++;
		}
		h = 0;
		j++;
	}
}
