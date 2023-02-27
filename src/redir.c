/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:05:51 by bperron           #+#    #+#             */
/*   Updated: 2023/02/27 14:21:30 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	relaunch(t_shell *shell, char *cmd, int i)
{
	dprintf(2, "MiniHell: parse error near '%c'\n", cmd[i]);
	free_arrarrarr(shell->cmds);
	free(shell->hold);
	launch_terminal(get_struc());
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

void	is_good_1(char **cmds, t_shell *shell)
{
	int	j;
	int	l;

	j = 0;
	while (cmds[j])
	{
		if ((cmds[j][0] == '<' || cmds[j][0] == '>') && cmds[j + 1])
		{
			l = 1;
			while (cmds[j + l][0] == ' ' && cmds[j + l])
				l++;
			if (cmds[j + l][0] == '<' || cmds[j + l][0] == '>')
				relaunch(shell, cmds[j + l], 0);
		}
		j++;
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
	shell->cmds[row] = ft_calloc(nb + 1, sizeof(char *));
	while (nb-- > 0)
	{
		k = 0;
		size = find_size(shell, j, 0, 0);
		shell->cmds[row][++i] = ft_calloc(size + 1, sizeof(char));
		while (size-- > 0)
			shell->cmds[row][i][k++] = shell->hold[j++];
		shell->status = 258;
		is_good(shell->cmds[row][i], shell, -1);
		shell->status = 0;
	}
	is_good_1(shell->cmds[row], shell);
}
