/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:25:46 by bperron           #+#    #+#             */
/*   Updated: 2023/02/23 13:46:12 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*rm_spaces(char *cmd, int len, int singles, int doubles)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = ft_calloc(sizeof(char), len + 1);
	i = -1;
	j = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ' ' && singles == 0 && doubles == 0)
			while (cmd[i + 1] == ' ')
				++i;
		else if (doubles == 0 && singles == 0 && cmd[i] == '"')
			doubles = 1;
		else if (singles == 0 && doubles == 0 && cmd[i] == '\'')
			singles = 1;
		else if (singles == 1 && cmd[i] == '\'')
			singles = 0;
		else if (doubles == 1 && cmd[i] == '"')
			doubles = 0;
		buffer[++j] = cmd[i];
	}
	free (cmd);
	return (buffer);
}

int	quotes_error(int singles, int doubles)
{
	if (singles % 2 == 1 || doubles % 2 == 1)
	{
		printf("minishell: syntax error near single or double quote\n");
		return (1);
	}
	return (0);
}

char	*space_quotes(char *cmd, int doubles, int singles, int i)
{
	int	j;

	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] == ' ' && singles % 2 == 0 && doubles % 2 == 0)
		{
			i++;
			while (cmd[i++] == ' ')
				++j;
		}
		if (singles % 2 == 0 && cmd[i] == '"')
			doubles++;
		else if (doubles % 2 == 0 && cmd[i] == '\'')
			singles++;
	}
	if (quotes_error(singles, doubles))
	{
		free(cmd);
		return (NULL);
	}
	cmd = rm_spaces(cmd, i - j + 1, 0, 0);
	return (cmd);
}

char	*remove_spaces(char *cmd)
{
	char	*hold;

	hold = ft_strtrim(cmd, " \t");
	free(cmd);
	cmd = hold;
	cmd = space_quotes(cmd, 0, 0, -1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	trim(t_shell *shell, int row)
{
	int		i;
	char	*hold;

	i = -1;
	while (shell->cmds[row][++i])
	{
		hold = ft_strtrim(shell->cmds[row][i], " \t");
		free(shell->cmds[row][i]);
		shell->cmds[row][i] = hold;
		hold = NULL;
	}
}
