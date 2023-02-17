/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2023/02/03 11:49:38 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_vars *g_vars)
{
	int	i;

	i = -1;
	if (ft_argsize(g_vars->piped) == 1)
	{
		while (g_vars->env[++i])
			printf("%s\n", g_vars->env[i]);
		g_vars->last_status = 0;
	}
	else
	{
		errno = 2;
		g_vars->last_status = 2;
		ft_fprintf(2, "env: %s: ", g_vars->piped[g_vars->index + 1]);
		perror("");
	}
}

void	ft_export(t_vars *g_vars)
{
	int		args;
	int		row;

	row = g_vars->index;
	args = ft_argsize(g_vars->piped);
	if (args > 1)
	{
		while (args > 1 && g_vars->piped[row][0] != '|')
		{
			row++;
			if (ft_strchr(g_vars->piped[row], '='))
			{	
				if (check_if_exist(g_vars, row) == 0)
					create_new_env(g_vars, row);
				g_vars->is_malloc = 1;
			}
			args--;
		}
	}
	else
		sort_env(g_vars);
	g_vars->last_status = 0;
}

void	create_new_env2(t_vars *g_vars, int row, int size)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_env = ft_calloc(sizeof(char *), size + 1);
	while (g_vars->env[++i])
	{
		if (ft_strncmp(g_vars->piped[row], g_vars->env[i],
				ft_strlen(g_vars->piped[row])) == 0)
			i++;
		new_env[++j] = g_vars->env[i];
	}
	new_env[++j] = 0;
	if (g_vars->is_malloc == 1)
		free(g_vars->env);
	g_vars->env = new_env;
}

void	check_if_good(t_vars *g_vars, int row, int *size, int *args)
{
	int	i;

	i = -1;
	while (g_vars->env[++i])
	{
		if (ft_strncmp(g_vars->piped[row], g_vars->env[i],
				ft_strlen(g_vars->piped[row])) == 0)
		{
			*size -= 1;
			*args -= 1;
			return ;
		}
	}
}

void	ft_unset(t_vars *g_vars)
{
	int		row;
	int		size;
	int		args;

	row = g_vars->index + 1;
	args = ft_argsize(g_vars->piped);
	if (args > 1)
	{
		while (args > 1 && g_vars->piped[row] && g_vars->piped[row][0] != '|')
		{
			size = ft_arrsize(g_vars->env);
			check_if_good(g_vars, row, &size, &args);
			create_new_env2(g_vars, row, size);
			row++;
		}
		g_vars->is_malloc = 1;
	}
	g_vars->last_status = 0;
}
