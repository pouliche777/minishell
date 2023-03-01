/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:57 by slord             #+#    #+#             */
/*   Updated: 2023/03/01 08:04:45 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	parsing(int row, t_shell *shell)
{
	shell->last_var = -1;
	shell->hold = remove_spaces(shell->hold);
	if (!shell->hold)
		return ;
	loop_var(shell, -1, 0, 0);
	check_redir(shell, row);
	if (shell->error == 0)
	{
		trim(shell, row);
		split_args(shell, row, -1, 0);
	}
}

int	is_space(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] != ' ')
			return (1);
	return (0);
}

static void	relaunch(char *cmd)
{
	dprintf(2, "MiniHell: parse error near '|'\n");
	free(cmd);
	get_struc()->error = 1;
}

void	check_pipes(int i, char *hold)
{
	int	j;

	if (hold[0] == '|' || hold[ft_strlen(hold) - 1] == '|')
		relaunch(hold);
	while (hold[++i])
	{
		if (hold[i] == '|')
		{
			j = 0;
			if (hold[++i + j] == '|')
				relaunch(hold);
			while ((hold[i + j] == ' ' || hold[i + j] == '\t') && hold[i + j])
			{
				if (hold[i + ++j] == '|')
					relaunch(hold);
			}
		}
	}
	free(hold);
}

void	lexer(char *buffer, t_shell *shell)
{
	char	**pre_c;
	int		i;
	int		j;

	i = 0;
	if (buffer[0] == '\0')
		return ;
	if (is_space(buffer) == 1)
	{
		check_pipes(-1, ft_strtrim(buffer, " \t"));
		if (shell->error == 0)
		{
			count_cmds(shell);
			j = shell->nb_cmds;
			shell->cmds = ft_calloc(sizeof(char **), j + 1);
			pre_c = split_pipe(buffer, j + 1);
			while (j-- > 0 && shell->error == 0)
			{
				shell->hold = pre_c[i];
				parsing(i, shell);
				free(shell->hold);
				shell->hold = NULL;
				i++;
			}
			free(pre_c);
		}
	}
}
