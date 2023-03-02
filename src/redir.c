/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:05:51 by bperron           #+#    #+#             */
/*   Updated: 2023/03/02 13:01:52 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	relaunch(t_shell *shell, char *cmd, int i)
{
	dprintf(2, "MiniHell: parse error near '%c'\n", cmd[i]);
	if (shell->cmds)
		free_arrarrarr(shell->cmds);
	shell->status = 258;
	shell->error = 1;
}

void	is_good(char *cmd, t_shell *shell, int i)
{
	if (cmd[0] == '>')
	{
		while (cmd[++i])
		{		
			if (cmd[i] != '>' || i > 1)
				relaunch(shell, cmd, i);
		}
	}
	else if (cmd[0] == '<')
	{
		while (cmd[++i])
		{
			if (cmd[i] != '<' || i > 1)
				relaunch(shell, cmd, i);
			if (cmd[i] != '<' || i > 1)
				relaunch(shell, cmd, i);
		}
	}
}

void	is_good_1(char **cmd, t_shell *shell)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
		{
			if (cmd[i + 1])
			{
				if (cmd[i + 1][0] == '>' || cmd[i + 1][0] == '<')
					relaunch(shell, cmd[i + 1], 0);
			}
		}
		if (i == arr_size(cmd) - 1 && (cmd[i][0] == '<' || cmd[i][0] == '>'))
			relaunch(shell, cmd[i], 0);
	}
}

void	first_redir(t_shell *shell)
{
	if (shell->hold[0] == '<' || shell->hold[0] == '>')
	{
		if (ft_strlen(shell->hold) >= 3)
		{
			if (shell->hold[0] == '<' && shell->hold[1] == '<')
				return ;
		}
		relaunch(shell, shell->hold, 0);
	}
}

void	check_redir(t_shell *shell, int row)
{
	int	nb;
	int	size;
	int	i;
	int	j;
	int	k;

	nb = count_redir(shell, 0, 0);
	i = -1;
	j = 0;
	first_redir(shell);
	if (shell->error == 0)
	{
		shell->cmds[row] = ft_calloc(nb + 1, sizeof(char *));
		while (nb-- > 0)
		{
			k = 0;
			size = find_size(shell, j, 0, 0);
			shell->cmds[row][++i] = ft_calloc(size + 1, sizeof(char));
			while (size-- > 0)
				shell->cmds[row][i][k++] = shell->hold[j++];
			is_good(shell->cmds[row][i], shell, -1);
		}
		is_good_1(shell->cmds[row], shell);
	}
}
