/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tardig <tardig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:13:56 by bperron           #+#    #+#             */
/*   Updated: 2023/02/26 20:52:17 by tardig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	check2(char **cmd, int row)
{
	int	i;

	i = 0;
	while (cmd[row][++i])
	{
		if (cmd[row][i] != 'n')
			return (1);
	}
	return (0);
}

int	check_flags(char **cmd, int *row)
{
	int		flags;
	int		hold;

	flags = 0;
	hold = *row;
	if (arr_size(cmd) > 1)
	{
		hold = ++*row;
		while (cmd[*row])
		{
			if (cmd[*row][0] == '-')
			{
				if (check2(cmd, *row) == 1)
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

void	print(char **cmd, int row)
{
	int	i;

	i = row - 1;
	if (arr_size(cmd) > 1)
	{
		while (cmd[++i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
		}
	}
}

void	echo(char **cmd)
{
	int	flags;
	int	row;

	row = 0;
	flags = check_flags(cmd, &row);
	if (flags == 0)
	{
		print(cmd, row);
		printf("\n");
	}
	else
		print(cmd, row);
	free_garbage(get_struc(), 0);
}
