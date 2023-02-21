/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:46:29 by bperron           #+#    #+#             */
/*   Updated: 2023/02/06 07:59:22 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (255);
		i++;
	}
	if (i > 19)
		return (20);
	else
		return (i);
}

void	set_status(t_vars *g_vars, unsigned char *status)
{
	if (check_arg(g_vars->piped[g_vars->index + 1]) > 19)
	{
		errno = 22;
		ft_fprintf(2, "Minishell: exit: %s: ",
			g_vars->piped[g_vars->index + 1]);
		perror("");
		*status = 255;
	}
	else
		*status = atoll(g_vars->piped[g_vars->index + 1]);
}

void	ft_exit(t_vars *g_vars)
{
	unsigned char	status;
	int				args;

	status = 0;
	printf("exit\n");
	args = ft_argsize(&g_vars->piped[g_vars->index]);
	if (args == 2)
	{
		set_status(g_vars, &status);
		free_garbage(g_vars, status);
	}
	else if (args == 1)
	{
		if (g_vars->last_status < 0 || g_vars->last_status > 255 )
			status = 1;
		else
			status = g_vars->last_status;
	}
	else
	{
		errno = 7;
		g_vars->last_status = 7;
		perror("Minishell: exit");
	}
	free_garbage(g_vars, status);
}
