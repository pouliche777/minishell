/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:07:15 by bperron           #+#    #+#             */
/*   Updated: 2023/02/02 14:36:55 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_vars *g_vars)
{
	char	*buf;

	buf = ft_calloc(sizeof(char), 1000);
	getcwd(buf, 1000);
	if (buf[0] != '\0')
	{
		printf("%s\n", buf);
		g_vars->last_status = 0;
	}
	else
	{
		g_vars->last_status = errno;
		perror("pwd");
	}
	free(buf);
}

void	change_pwd(char *old, char *new, t_vars *g_vars)
{
	int		i;

	i = -1;
	while (g_vars->env[++i])
	{
		if (ft_strnstr(g_vars->env[i], "PWD", 3) != NULL)
		{
			if (g_vars->cd == 1)
				free(g_vars->env[i]);
			g_vars->env[i] = ft_strjoin("PWD", new);
		}
		else if (ft_strnstr(g_vars->env[i], "OLDPWD", 6) != NULL)
		{
			if (g_vars->cd == 1)
				free(g_vars->env[i]);
			g_vars->env[i] = ft_strjoin("OLDPWD", old);
		}
	}
}

char	*find_path(t_vars *g_vars)
{
	int	i;

	i = -1;
	if (ft_argsize(g_vars->piped) > 1)
		return (g_vars->piped[g_vars->index + 1]);
	else
	{
		while (g_vars->env[++i])
		{
			if (ft_strnstr(g_vars->env[i], "HOME", 4) != NULL)
				return (&g_vars->env[i][5]);
		}
	}
	return (NULL);
}

void	ft_cd(t_vars *g_vars)
{
	char	*old;
	char	*new;

	old = ft_calloc(sizeof(char), 1000);
	new = ft_calloc(sizeof(char), 1000);
	getcwd(old, 1000);
	g_vars->last_status = chdir(find_path(g_vars));
	change_pwd(old, getcwd(new, 1000), g_vars);
	free(old);
	free(new);
	g_vars->cd = 1;
	if (g_vars->last_status != 0)
	{
		ft_fprintf(2, "cd: %s: ", g_vars->piped[g_vars->index + 1]);
		g_vars->last_status = 1;
		perror("");
	}
	else
		g_vars->last_status = 0;
}
