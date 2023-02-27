/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tardig <tardig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:17:48 by slord             #+#    #+#             */
/*   Updated: 2023/02/26 20:43:43 by tardig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	check_v(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	free(shell->variable);
	shell->variable = NULL;
	while (shell->env[i])
	{
		if (!(ft_strncmp(var, shell->env[i], ft_strlen(var)))
			&& shell->env[i][ft_strlen(var)] == '=')
		{
			shell->variable = ft_strdup(&shell->env[i][ft_strlen(var) + 1]);
			return (ft_strlen(shell->variable));
		}
		i++;
	}
	return (0);
}
