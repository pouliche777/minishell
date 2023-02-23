/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:29 by bperron           #+#    #+#             */
/*   Updated: 2023/02/22 08:38:59 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arrarrarr(char ***arr)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (arr[++i])
	{
		while (arr[i][++j])
			free(arr[i][j]);
		free(arr[i]);
	}
	free(arr);
}

void	free_garbage(t_shell *shell, unsigned char status)
{
	free_env(shell);
	if (shell->cmds)
		free_arrarrarr(shell->cmds);
	exit(status);
}
