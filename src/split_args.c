/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:35:19 by bperron           #+#    #+#             */
/*   Updated: 2023/02/22 14:31:25 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

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
		i++;
	}
	return (i - start);
}

void	split_args(t_shell *shell, int row, int i, int j)
{
	char	**new;
	int		size;
	int		size2;
	int		k;
	int		m;
	
	size = count_args(shell->cmds[row], 1);
	new = ft_calloc(size + 2, sizeof(char *));
	m = 0;
	while (size-- > 1)
	{
		k = -1;
		size2 = find_arg_size(shell->cmds[row][m], j);
		new[++i] = ft_calloc(size2 + 1, sizeof(char));
		while (size2-- > 0)
			new[i][++k] = shell->cmds[row][m][j++];
		j++;
		if (j >= (int) ft_strlen(shell->cmds[row][m]))
		{
			m++;
			j = 0;
		}
	}
	free_pp((void *) shell->cmds[row]);
	shell->cmds[row] = new;
}

int	cmd_lenght(char *cmd, int start)
{
	int	i;

	i = start;
	while(cmd[i] != '|' && cmd[i])
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

char	**split_pipe(char *cmd, int nb)
{
	char	**split;
	int		size;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	split = ft_calloc(nb + 1, sizeof(char *));
	while (i < (int) ft_strlen(cmd))
	{
		k = -1;
		size = cmd_lenght(cmd, i);
		split[++j] = ft_calloc(sizeof(char), size + 1);
		while (--size >= 0)
			split[j][++k] = cmd[i++];
		i++;
	}
	return (split);
}
