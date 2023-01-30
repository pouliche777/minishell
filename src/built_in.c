/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:13:30 by slord             #+#    #+#             */
/*   Updated: 2023/01/30 17:50:59 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	pwd(t_shell *shell, char **cmds, int i)
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

int	echo(t_shell *shell, char **cmds, int i)
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

int	export(t_shell *shell, char **cmds)
{
	char	*var;
	int		i;

	i = 0;
	if (cmds[1]== NULL)
		env(shell);
	else if (cmds[2]== NULL && ft_isdigit(cmds[1][0]) == 0)
	{
		while (cmds[1][i] != '=' &&cmds[1][i])
			i++;
		var = ft_substr(cmds[1], 0, i);
		if (check_v(shell, var) == 1)
		{
			replace_var(shell, var);
			free(var);
		}
		else
			if (ft_strchr(cmds[1], '=') != 0)
				modify_env(shell, cmds[1]);
	}
	else
	{
		printf("mauvais input pour export \n");
		return (0);
	}
	return (1);
}

int	unset(t_shell *shell, char **cmds)
{
	if (check_var(shell, cmds[1]) == 1)
		return (1);
	else 
		return (2);
}

void	exit_built_in(t_shell *shell)
{
	close_fd();
	clear_history();
	free (shell);
	exit(0);
}
//int cd(t_shell *shell, char ***cmds)
//{
//	chdir()
//}