/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:29:58 by slord             #+#    #+#             */
/*   Updated: 2023/02/28 18:52:57 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	delete_env(t_shell *shell, char *var_name)
{
	int		i;
	char	**temp;
	int		j;

	i = 0;
	j = 0;
	while (shell->env[i])
		i++;
	temp = ft_calloc(sizeof (char *), i + 2);
	i = -1;
	while (shell->env[++i])
		temp[i] = ft_strdup(shell->env[i]);
	free_env(shell);
	shell->env = ft_calloc(sizeof (char *), i + 1);
	i = -1;
	while (temp[++i])
	{
		if (ft_strncmp(var_name, temp[i], ft_strlen(var_name)) == 0)
			i++;
		if (temp[i])
			shell->env[j] = ft_strdup(temp[i]);
		j++;
	}
	free(temp);
}

void	init_env(t_shell *shell, char **env)
{
	int		j;

	j = 0;
	while (env[j])
		j++;
	j--;
	shell->env = ft_calloc(j + 2, sizeof(char *));
	while (j >= 0)
	{
		shell->env[j] = ft_strdup(env[j]);
		j--;
	}
}
