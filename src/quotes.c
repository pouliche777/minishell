/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:24:25 by slord             #+#    #+#             */
/*   Updated: 2023/01/23 20:30:18 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	count_nb_quotes(char *str)
{
	int	i;
	int	nb_quotes;

	i = 0;
	nb_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			nb_quotes = nb_quotes + 2;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{		
			i++;
			nb_quotes = nb_quotes + 2;
			while (str[i] != '\"')
				i++;
		}
		i++;
	}
	return (nb_quotes);
}

void	supress_quotes(t_shell *shell, char *temp, int i, int j)
{
	int	h;
	int	k;

	h = 0;
	k = 0;
	while (temp[k])
	{
		if (temp[k] == '\'')
		{
			k++;
			while (temp[k] != '\'')
			{
				shell->cmds[i][j][h] = temp[k];
				h++;
				k++;
			}		
		}
		else if (temp[k] == '\"')
		{
			k++;
			while (temp[k] != '\"')
			{
				shell->cmds[i][j][h] = temp[k];
				h++;
				k++;
			}	
		}
		else
		{
			shell->cmds[i][j][h] = temp[k];
			h++;
		}
		k++;
	}
}

void	check_quotes(t_shell *shell, int i, int j)
{
	int		nb_quotes;
	char	*temp;

	while (shell->cmds[i][j])
	{
		nb_quotes = count_nb_quotes(shell->cmds[i][j]);
		if (nb_quotes > 0)
		{
			temp = ft_strdup(shell->cmds[i][j]);
			free (shell->cmds[i][j]);
			shell->cmds[i][j] = NULL;
			shell->cmds[i][j] = ft_calloc(1, ft_strlen(temp) - nb_quotes + 1);
			supress_quotes(shell, temp, i, j);
			free(temp);
		}
		j++;
	}
}
