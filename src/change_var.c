/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:09:38 by bperron           #+#    #+#             */
/*   Updated: 2023/02/16 08:46:12 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	loop_var(t_shell *shell, int i, int doubles, int singles)
{
	while (shell->hold[++i])
	{
		if (shell->hold[i] == '"' && singles % 2 == 0)
			doubles++;
		else if (shell->hold[i] == '\'' && doubles % 2 == 0)
			singles++;
		if (shell->hold[i] == '$' && singles % 2 != 1
			&& ((shell->hold[i + 1] >= 'a' && shell->hold[i + 1] <= 'z')
				|| (shell->hold[i + 1] >= 'A' && shell->hold[i + 1] <= 'Z')
				|| shell->hold[i + 1] == '_') && i > shell->last_var
			&& redir_check(shell->hold, i))
		{
			find_var(shell, i + 1);
			break ;
		}
		else if (shell->hold[i] == '$' && singles % 2 != 1
			&& shell->hold[i + 1] == '?' && i > shell->last_var)
		{
			status(shell, -1, -1, -1);
			break ;
		}
	}
}

void	status(t_shell *shell, int i, int j, int k)
{
	char	*nb;
	char	*new;

	nb = ft_itoa(shell->status);
	new = ft_calloc(ft_strlen(shell->hold) + ft_strlen(nb) + 1, sizeof(char));
	while (shell->hold[++i] != '$' && shell->hold[i + 1] != '?')
		new[++j] = shell->hold[i];
	i += 1;
	while (nb[++k])
		new[++j] = nb[k];
	while (shell->hold[++i])
		new[++j] = shell->hold[i];
	free(shell->hold);
	free(nb);
	shell->hold = new;
	loop_var(shell, -1, 0, 0);
}

void	find_var(t_shell *shell, int i)
{
	char	*hold;
	char	*var;
	int		exist;
	int		j;

	exist = 0;
	j = end_while(shell, i, 0);
	hold = ft_substr(shell->hold, i, j);
	var = ft_strjoin(hold, "=");
	free(hold);
	j = -1;
	while (shell->env[++j])
	{
		if (ft_strnstr(shell->env[j], var, ft_strlen(var)) != NULL)
		{
			exist = 1;
			break ;
		}
	}
	if (exist == 1)
		change_var(shell, i - 1, j, ft_strlen(var));
	else
		remove_var(shell, i - 1, ft_strlen(var));
	free(var);
}

void	remove_var(t_shell *shell, int var_place, int size)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(shell->hold) - size + 1, sizeof(char));
	i = -1;
	j = -1;
	while (shell->hold[++i])
	{
		if (i == var_place)
		{
			while (size--)
				i++;
		}
		new[++j] = shell->hold[i];
	}
	free(shell->hold);
	shell->hold = new;
	loop_var(shell, -1, 0, 0);
}

void	change_var(t_shell *shell, int var_place, int env_place, int len)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(shell->hold)
			- ft_strlen_until(shell->env[env_place],
				'=') + find_var_len(shell, env_place) + 1, sizeof(char));
	if (new == NULL)
		return ;
	i = -1;
	j = -1;
	while (++i < var_place)
		new[++j] = shell->hold[i];
	i += len;
	j++;
	j = put_new_var(shell, new, var_place, env_place);
	while (shell->hold[i])
		new[j++] = shell->hold[i++];
	new[j] = '\0';
	free(shell->hold);
	shell->hold = new;
	loop_var(shell, -1, 0, 0);
}