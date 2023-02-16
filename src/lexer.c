/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:57 by slord             #+#    #+#             */
/*   Updated: 2023/02/16 13:46:28 by bperron          ###   ########.fr       */
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
	for (int i = 0; shell->cmds[i]; i++)
		for (int j = 0; shell->cmds[i][j]; j++)
			printf("%s\n", shell->cmds[i][j]);
}

void	lexer(char *buffer, t_shell *shell)
{
	char	**pre_c;
	int		i;
	int		j;

	i = 0;
	if (buffer[0] == '\0')
		return ;
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

