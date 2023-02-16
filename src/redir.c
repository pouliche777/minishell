/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:05:51 by bperron           #+#    #+#             */
/*   Updated: 2023/02/16 08:48:07 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	count_redir(t_shell *shell, int singles, int doubles)
{
	int	nb;
	int	i;

	i = -1;
	nb = 0;
	if (shell->hold[0] != '<' && shell->hold[0] != '>')
		nb++;
	while (shell->hold[++i])
	{
		if (shell->hold[i] == '"' && singles % 2 == 0)
			doubles++;
		else if (shell->hold[i] == '\'' && doubles % 2 == 0)
			singles++;
		if ((shell->hold[i] == '>' || shell->hold[i] == '<') && singles % 2 == 0 && doubles % 2 == 0)
		{
			while (shell->hold[i] == '>' || shell->hold[i] == '<')
				i++;
			nb++;
			if (shell->hold[i])
				nb++;
		}
	}
	return (nb);
}

int	find_size(t_shell *shell, int i, int doubles, int singles)
{
	int	size;

	size = 0;
	if ((shell->hold[i] == '>' || shell->hold[i] == '<'))
	{
		while ((shell->hold[i] == '>' || shell->hold[i] == '<') && shell->hold[i++])
			size++;
	}
	else
	{
		while (shell->hold[i])
		{
			if (shell->hold[i] == '"' && singles % 2 == 0)
				doubles++;
			else if (shell->hold[i] == '\'' && doubles % 2 == 0)
				singles++;
			if ((shell->hold[i] == '>' || shell->hold[i] == '<')
				&& singles % 2 == 0 && doubles % 2 == 0)
				break ;
			size++;
			i++;
		}
	}
	return (size);
}

void	check_redir(t_shell *shell, int row)
{
 	int		nb;
	int		size;
 	int		i;
	int		j;
	int		k;

	nb = count_redir(shell, 0, 0);
	i = 0;
	j = 0;
	shell->cmds[row] = ft_calloc(nb + 1, sizeof(char *));
	while (nb-- > 0)
	{
		k = 0;
		size = find_size(shell, j, 0, 0);
		shell->cmds[row][i] = ft_calloc(size + 1, sizeof(char));
		while (size-- > 0)
			shell->cmds[row][i][k++] = shell->hold[j++];
	}
}