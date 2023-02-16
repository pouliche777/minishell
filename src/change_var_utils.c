/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:10:51 by bperron           #+#    #+#             */
/*   Updated: 2023/02/16 08:46:09 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	put_new_var(t_shell *shell, char *new, int var_place, int env_place)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new[j])
		j++;
	while (shell->env[env_place][i] != '=')
		i++;
	i++;
	shell->last_var = var_place + i - 2;
	while (shell->env[env_place][i])
		new[j++] = shell->env[env_place][i++];
	return (j);
}

int	find_var_len(t_shell *shell, int env_place)
{
	char	*hold;

	hold = shell->env[env_place];
	while (*hold != '=')
		hold++;
	hold++;
	return (ft_strlen(hold));
}

int	end_while(t_shell *shell, int i, int j)
{
	while (shell->hold[i + j] && ((shell->hold[i + j] >= 'a'
				&& shell->hold[i + j] <= 'z') || (shell->hold[i + j] >= 'A'
				&& shell->hold[i + j] <= 'Z') || (shell->hold[i + j] >= '0'
				&& shell->hold[i + j] <= '9') || shell->hold[i + j] == '_'))
		++j;
	return (j);
}

int	redir_check(char *cmd, int i)
{
	i--;
	while (i >= 0 && (cmd[i] == ' ' || cmd[i] == '\''
			|| cmd[i] == '\"'))
		i--;
	if (i >= 1)
		if (cmd[i - 1] == '<' && cmd[i] == '<')
			return (0);
	return (1);
}