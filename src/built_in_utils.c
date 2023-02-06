/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:38:44 by slord             #+#    #+#             */
/*   Updated: 2023/02/06 16:27:46 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_built_in(t_shell *shell, int i)
{
	supress_operators(shell, i);
	if (ft_strncmp(shell->cmds[i][0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(shell->cmds_exe[0], "pwd", 4) == 0)
		return (pwd(shell, i));
	if (ft_strncmp(shell->cmds_exe[0], "echo", 5) == 0)
		return (echo(shell->cmds_exe));
	if (ft_strncmp(shell->cmds[i][0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(shell->cmds_exe[0], "env", 4) == 0)
		return (env(shell));
	if (ft_strncmp(shell->cmds[i][0], "unset", 6) == 0)
		return (1);
	return (0);
}

void	check_built_in_parent(t_shell *shell, int i)
{
	if (ft_strncmp(shell->cmds[i][0], "export", 7) == 0)
		export(shell, shell->cmds[0]);
	if (ft_strncmp(shell->cmds[i][0], "exit", 5) == 0)
		exit_built_in(shell, shell->cmds[0][1]);
	if (ft_strncmp(shell->cmds[i][0], "unset", 6) == 0)
		unset(shell, shell->cmds[i][1]);
	if (ft_strncmp(shell->cmds[i][0], "cd", 2) == 0)
		cd_built_in(shell, shell->cmds[0][1]);
}


void	modify_env_1(t_shell *shell, int i)
{
	int		j;
	int		h;
	int		k;
	char	**temp;

	j = 0;
	h = 0;
	k = 0;
	while (shell->env[j])
		j++;
	temp = malloc(sizeof(char *) * j + 1);
	j--;
	while (k <= j)
	{
		if (h == i)
		{
			free(shell->env[k]);
			k++;
		}
		if (k <= j)
		{
			temp[h] = ft_strdup(shell->env[k]);
			free(shell->env[k]);
		}
		h++;
		k++;
	}
	free(shell->env);
	shell->env = malloc(sizeof(char *) * j + 1);
	j--;
	while (j >= 0)
	{
		shell->env[j] = ft_strdup(temp[j]);
		free(temp[j]);
		j--;
	}
	free(temp);
}

int	check_var(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
		{
			modify_env_1(shell, i);
			return (1);
		}
		i++;
	}
	return (0);
}