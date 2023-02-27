/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:57 by slord             #+#    #+#             */
/*   Updated: 2023/02/27 10:32:15 by bperron          ###   ########.fr       */
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
	trim(shell, row);
	split_args(shell, row, -1, 0);
}

void	is_space(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] != ' ')
			return ;
	launch_terminal(get_struc());
}

static void	relaunch(char *cmd)
{
	printf("MiniHell: parse error near '|'\n");
	free(cmd);
	launch_terminal(get_struc());
}

void	check_pipes(int i, int j, char *hold)
{
	if (hold[0] == '|' || hold[ft_strlen(hold) - 1] == '|')
		relaunch(hold);
	while (hold[++i])
	{
		if (hold[i] == '|')
		{
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
	is_space(buffer);
	check_pipes(-1, 0, ft_strtrim(buffer, " \t"));
	count_cmds(shell);
	j = shell->nb_cmds;
	shell->cmds = ft_calloc(sizeof(char **), j + 1);
	pre_c = split_pipe(buffer, j + 1);
	while (j-- > 0)
	{
		shell->hold = pre_c[i];
		parsing(i, shell);
		free(shell->hold);
		shell->hold = NULL;
		i++;
	}
	free(pre_c);
}
