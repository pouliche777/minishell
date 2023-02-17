/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:05:24 by bperron           #+#    #+#             */
/*   Updated: 2023/02/03 11:49:58 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_exist(t_vars *g_vars, int row)
{
	int	size;
	int	i;

	size = ft_strlen_until(g_vars->piped[row], '=');
	i = -1;
	while (g_vars->env[++i])
	{
		if (ft_strlen_until(g_vars->piped[row], '=')
			== ft_strlen_until(g_vars->env[i], '='))
		{
			if (ft_strncmp(g_vars->piped[row], g_vars->env[i], size) == 0)
			{
				g_vars->env[i] = ft_substr(g_vars->piped[row], 0,
						ft_strlen(g_vars->piped[row]));
				return (1);
			}
		}
	}	
	return (0);
}

void	create_new_env(t_vars *g_vars, int row)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (g_vars->env[i])
		i++;
	new_env = ft_calloc(i + 3, sizeof(char *));
	while (++j < i - 1)
		new_env[j] = g_vars->env[j];
	new_env[j] = ft_substr(g_vars->piped[row], 0,
			ft_strlen(g_vars->piped[row]));
	ft_lstadd_back(&g_vars->garbage, ft_lstnew((void *) new_env[j]));
	new_env[j + 1] = g_vars->env[j];
	if (g_vars->is_malloc == 1)
		free(g_vars->env);
	g_vars->env = new_env;
}

void	print_sorted(char **sorted)
{
	int	i;
	int	j;

	i = -1;
	while (sorted[++i])
	{
		j = -1;
		ft_fprintf(1, "declare -x ");
		while (sorted[i][++j] != '=')
			ft_putchar_fd(sorted[i][j], 1);
		ft_putchar_fd(sorted[i][j++], 1);
		ft_fprintf(1, "\"%s\"\n", sorted[i]);
	}
}

void	sorting(char **sorted, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1 - i)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
		}
	}
}

void	sort_env(t_vars *g_vars)
{
	int		size;
	int		i;
	char	**sorted;

	size = 0;
	while (g_vars->env[size])
		size++;
	sorted = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (g_vars->env[++i])
		sorted[i] = g_vars->env[i];
	sorting(sorted, size);
	print_sorted(sorted);
	free(sorted);
}
