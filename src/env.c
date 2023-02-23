/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:11:44 by slord             #+#    #+#             */
/*   Updated: 2023/02/23 13:14:56 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	check_if_var_exist(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->var_name, shell->env[i],
				ft_strlen(shell->var_name)) == 0)
			return (1);
		i++;
		j++;
	}
	return (0);
}

void	replace_var_1(t_shell *shell, char *var_line)
{
	int	i;

	i = 0;
	while ((ft_strncmp(shell->var_name, shell->env[i],
				ft_strlen(shell->var_name))) != 0)
		i++;
	free(shell->env[i]);
	shell->env[i] = ft_strdup(var_line);
}

void	get_var(t_shell *shell, char *var_line)
{
	int	i;

	i = 0;
	while (var_line[i] != '=')
		i++;
	shell->var_name = ft_substr(var_line, 0, i);
	shell->var = ft_strdup(var_line + i);
}

void	add_env(t_shell *shell, char *var_line, int j)
{
	int		i;
	char	**temp;

	get_var(shell, var_line);
	i = -1;
	if (check_if_var_exist(shell) == 1)
	{
		replace_var_1(shell, var_line);
		return ;
	}
	while (shell->env[++i])
	j = 0;
	temp = calloc(sizeof (char *), i + 1);
	i = -1;
	while (shell->env[++i])
		temp[i] = ft_strdup(shell->env[i]);
	free_env(shell);
	shell->env = calloc(sizeof (char *), i + 2);
	i = -1;
	while (temp[++i])
		shell->env[i] = ft_strdup(temp[i]);
	shell->env[i] = ft_strdup(var_line);
	shell->env[i + 1] = NULL;
	free(temp);
}
