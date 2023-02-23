/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:57:37 by slord             #+#    #+#             */
/*   Updated: 2022/11/14 23:24:10 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	get_path(t_shell *info)
{
	int		i;
	char	*str;

	i = 0;
	while (ft_strncmp(info->env[i], "PATH=", 5) != 0)
		i++;
	str = info->env[i] + 5;
	info->path = ft_split(str, ':');
}

int	count_nb_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
	printf("%d \n", i);
}

int	count_nb_token(char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
		i++;
	return (i);
}

void	free_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		shell->env[i] = NULL;
		free(shell->env[i]);
		i++;
	}
	shell->env = NULL;
	free(shell->env);
}
