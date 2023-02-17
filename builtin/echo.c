/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:24:02 by bperron           #+#    #+#             */
/*   Updated: 2023/02/03 11:28:08 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check2(t_vars *g_vars, int row)
{
	int	i;

	i = 0;
	while (g_vars->piped[row][++i])
	{
		if (g_vars->piped[row][i] != 'n')
			return (1);
	}
	return (0);
}

int	check_flags(t_vars *g_vars, int *row)
{
	int		flags;
	int		hold;

	flags = 0;
	hold = *row;
	if (ft_argsize(g_vars->piped) > 1)
	{
		hold = ++*row;
		while (g_vars->piped[*row])
		{
			if (g_vars->piped[*row][0] == '-')
			{
				if (check2(g_vars, *row) == 1)
					return (flags);
				flags = 1;
				hold++;
			}
			else
				return (flags);
			*row += 1;
		}
		*row += 1;
	}
	*row = hold;
	return (flags);
}

void	print(t_vars *g_vars, int row)
{
	int	arg;

	if (ft_argsize(g_vars->piped) > 1)
	{
		arg = ft_argsize(g_vars->piped) - row - 2;
		while (arg-- > -1)
			if (g_vars->piped[row] != NULL && g_vars->piped[row][0] != '|')
				printf("%s ", g_vars->piped[row++]);
		if (g_vars->piped[row])
			if (g_vars->piped[row][0] != '|')
				printf("%s", g_vars->piped[row]);
	}
}

void	ft_echo(t_vars *g_vars)
{
	int	flags;
	int	row;

	row = g_vars->index;
	flags = check_flags(g_vars, &row);
	if (flags == 0)
	{
		print(g_vars, row);
		printf("\n");
	}
	else
		print(g_vars, row);
}
