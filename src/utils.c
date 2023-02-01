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

#include "shell.h"

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

void	free_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (shell->cmds[i])
	{
		while (shell->cmds[i][j])
		{
			free(shell->cmds[i][j]);
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	while (shell->cmds[i])
	{
		free(shell->cmds[i]);
		i++;
	}
	if (shell->cmds)
	{
		free(shell->cmds);
		shell->cmds = NULL;
	}
}

void	close_fd(void)
{
	int	i;

	i = 0;
	while (i < 101)
	{
		close(i);
		i++;
	}
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