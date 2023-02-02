/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:13:30 by slord             #+#    #+#             */
/*   Updated: 2023/02/01 19:07:24 by slord            ###   ########.fr       */
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
	int		i;

	i = 0;
	if (cmds[1]== NULL)
	{
		env(shell);
		return (1);
	}
		
	/* else if (cmds[2]== NULL && ft_isdigit(cmds[1][0]) == 0)
	{
		while (cmds[1][i] != '=' &&cmds[1][i])
			i++;
		var = ft_substr(cmds[1], 0, i);
		if (check_v(shell, var) == 1)
		{
			replace_var(shell, var);
			free(var);
		}
	*/
	
	if (ft_strchr(cmds[1], '=') != 0 && ft_isdigit(cmds[1][0]) == 0 && cmds[2]== NULL)
	{
		printf("dsada\n");
		add_env(shell, cmds[1]);
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

void	exit_built_in(t_shell *shell, char *exit_arg)
{
	int	i;

	i = 0;
	close_fd();
	clear_history();
	free(shell);
	if (!exit_arg)
		exit(0);
	while (ft_isdigit(exit_arg[i]))
		i++;
	if (exit_arg[i] == '\0')
		exit(ft_atoi(exit_arg));
	else
	{
		printf("bash: exit: dsaas: numeric argument required \n");
		exit (255);
	}
}

char	*get_pwd(char **env)
{
	char	*pwd;
	int		j;

	j = 0;
	while (ft_strncmp(env[j], "PWD=", 4))
		j++;
	pwd = env[j] + 4;
	return (pwd);
}
char	*get_old_pwd(char **env)
{
	char	*old_pwd;
	int		j;

	j = 0;
	while (ft_strncmp(env[j], "OLDPWD=", 7))
		j++;
	old_pwd = env[j] + 7;
	return (old_pwd);
}

int	cd_built_in(t_shell *shell, char *path)
{
	char	*current_path;
	char	*old_path;
	char	buff[1024];

	old_path = getcwd(buff, 1024);
	if (chdir(path) != 0)
	{
		printf("cd, error \n");
		return (1);
	}
	old_path = ft_strjoin("OLDPWD=", old_path);
	current_path = getcwd(buff, 1024);
	current_path = ft_strjoin("PWD=", current_path);
	if (path[0]== '.')
		add_env(shell, current_path);
	else
		add_env(shell, current_path);
	add_env(shell, old_path);
	free(current_path);
	free(old_path);
	return (1);
}