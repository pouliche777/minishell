/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:24:25 by slord             #+#    #+#             */
/*   Updated: 2023/02/24 07:38:31 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

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

void	suppress_quotes(t_shell *shell, char *temp, int i)
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
				shell->cmds_exe[i][h++] = temp[k++];
		}
		else if (temp[k] == '\"')
		{
			k++;
			while (temp[k] != '\"')
				shell->cmds_exe[i][h++] = temp[k++];
		}
		else
			shell->cmds_exe[i][h++] = temp[k];
		k++;
	}
}

void	check_quotes(t_shell *shell)
{
	int		nb_quotes;
	char	*temp;
	int		i;

	i = 0 ;
	while (shell->cmds_exe[i])
	{
		nb_quotes = count_nb_quotes(shell->cmds_exe[i]);
		if (nb_quotes > 0)
		{
			temp = ft_strdup(shell->cmds_exe[i]);
			free (shell->cmds_exe[i]);
			shell->cmds_exe[i] = NULL;
			shell->cmds_exe[i] = ft_calloc(1, ft_strlen(temp) - nb_quotes + 1);
			suppress_quotes(shell, temp, i);
			free(temp);
		}
		i++;
	}
}
