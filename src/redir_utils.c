/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:19:17 by bperron           #+#    #+#             */
/*   Updated: 2023/02/27 14:21:13 by bperron          ###   ########.fr       */
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
		if ((shell->hold[i] == '>' || shell->hold[i] == '<')
			&& singles % 2 == 0 && doubles % 2 == 0)
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
		while ((shell->hold[i] == '>' || shell->hold[i] == '<')
			&& shell->hold[i++])
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
