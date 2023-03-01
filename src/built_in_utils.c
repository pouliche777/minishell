/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:38:44 by slord             #+#    #+#             */
/*   Updated: 2023/03/01 10:44:29 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	cmp(char *cmd, char *ref, int nb)
{
	int		i;
	char	*hold;

	i = -1;
	if (cmd)
	{
		hold = strdup(cmd);
		while (cmd[++i])
			hold[i] = ft_tolower(hold[i]);
		i = ft_strncmp(hold, ref, nb);
		free(hold);
	}
	return (i);
}

int	pwd(t_shell *shell)
{
	char	pwd[2000];
	int		j;

	j = 0;
	while (ft_strncmp(shell->env[j], "PWD=", 4))
		j++;
	getcwd(pwd, 2000);
	printf("%s\n", pwd);
	return (0);
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
	return (0);
}

int	check_built_in(t_shell *shell, int i)
{
	supress_operators(shell, i);
	check_quotes(shell);
	if (!shell->cmds_exe[0])
		return (1);
	if (cmp(shell->cmds_exe[0], "cd", 3) == 0)
		free_garbage(shell, cd_built_in(shell, shell->cmds[i][1]));
	else if (cmp(shell->cmds_exe[0], "pwd", 4) == 0)
		free_garbage(shell, pwd(shell));
	else if (cmp(shell->cmds_exe[0], "echo", 5) == 0)
		echo(shell->cmds_exe);
	else if (cmp(shell->cmds_exe[0], "export", 7) == 0)
		free_garbage(shell, export(shell, shell->cmds_exe));
	else if (cmp(shell->cmds_exe[0], "env", 4) == 0)
		free_garbage(shell, env(shell));
	else if (cmp(shell->cmds_exe[0], "unset", 6) == 0)
		free_garbage(shell, unset(shell, shell->cmds_exe[1]));
	else if (cmp(shell->cmds_exe[0], "exit", 4) == 0)
		exit_built_in(shell, shell->cmds_exe);
	return (0);
}

void	check_built_in_parent(t_shell *shell, int i) 
{
	supress_operators(shell, i);
	check_quotes(shell);
	if (cmp(shell->cmds_exe[0], "export", 7) == 0)
		export(shell, shell->cmds_exe);
	else if (cmp(shell->cmds_exe[0], "exit", 5) == 0)
		exit_built_in(shell, shell->cmds_exe);
	else if (shell->cmds_exe[1] && cmp(shell->cmds_exe[0], "unset", 6) == 0)
		unset(shell, shell->cmds_exe[1]);
	else if (cmp(shell->cmds_exe[0], "cd", 2) == 0)
		cd_built_in(shell, shell->cmds_exe[1]);
	else
	{
		free_pp((void *) shell->cmds_exe);
		return ;
	}
	free_pp((void *) shell->cmds_exe);
	shell->cmds_exe = NULL;
	close_fds(shell);
	shell->terminal = 1;
}
