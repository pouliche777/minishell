/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:38:44 by slord             #+#    #+#             */
/*   Updated: 2023/02/13 15:35:42 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	echo(char **cmds)
{
	int		j;

	j = 1;
	if (!cmds[1])
		printf("\n");
	if (!ft_strncmp(cmds[1], "-n", 3))
		j++;
	while (cmds[j])
	{
		printf("%s", cmds[j]);
		if (cmds[j + 1])
			printf(" ");
		j++;
	}
	if (ft_strncmp(cmds[1], "-n", 3))
		printf("\n");
	return (1);
}

int	pwd(t_shell *shell, int i)
{
	char	*pwd;
	int		j;

	j = 0;
	while (ft_strncmp(shell->env[j], "PWD=", 4))
		j++;
	pwd = shell->env[j] + 4;
	printf("%s\n", pwd);
	change_in_and_out(shell, i);
	return (1);
}

int	env(t_shell *shell)
{
	int		j;

	j = 0;
	while (shell->env[j])
	{
		printf("%s\n", shell->env[j]);
		j++;
	}
	return (1);
}

int	check_built_in(t_shell *shell, int i)
{
	supress_operators(shell, i);
	check_quotes(shell);
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
	//enveler les quotes
	if (ft_strncmp(shell->cmds[i][0], "export", 7) == 0)
		export(shell, shell->cmds[0]);
	if (ft_strncmp(shell->cmds[i][0], "exit", 5) == 0)
		exit_built_in(shell, shell->cmds[0][1]);
	if (ft_strncmp(shell->cmds[i][0], "unset", 6) == 0)
		unset(shell, shell->cmds[i][1]);
	if (ft_strncmp(shell->cmds[i][0], "cd", 2) == 0)
		cd_built_in(shell, shell->cmds[0][1]);
}
