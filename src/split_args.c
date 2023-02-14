/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:35:19 by bperron           #+#    #+#             */
/*   Updated: 2023/02/14 10:35:39 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"'

int	count_args(char **cmd, int nb)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '"')
			{
				while (cmd[i][++j] != '"')
					(void) j;
			}
			else if (cmd[i][j] == '\'')
			{
				while (cmd[i][++j] != '\'')
					(void) j;
			}
			if (cmd[i][j] == ' ')
				nb++;
		}
		nb++;
	}
	return (nb);
}

int	find_arg_size(char *cmd, int start)
{
	int	i;

	i = start;
	while(cmd[i] != ' ' && cmd[i])
	{
		i++;
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] != '"' && cmd[i])
				i++;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i])
				i++;
		}
	}
	return (i - start);
}

void	split_args(t_shell *shell, int row, int i, int j)
{
	char	**new;
	int		size;
	int		size2;
	int		k;
	
	size = count_args(shell->cmds[row], 1);
	new = ft_calloc(size + 1, sizeof(char *));
	while (size-- > 1)
	{
		k = -1;
		size2 = find_arg_size(shell->cmds[row][0], j);
		new[++i] = ft_calloc(size2 + 1, sizeof(char));
		while (size2-- > 0)
			new[i][++k] = shell->cmds[row][0][j++];
		j++;
		printf("%s\n", new[i]);
	}
	new[i] = NULL;
	free_pp((void *) shell->cmds[row]);
	shell->cmds[row] = new;
}
