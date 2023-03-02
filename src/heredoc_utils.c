/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:31:53 by slord             #+#    #+#             */
/*   Updated: 2023/03/02 12:35:08 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	heredoc_1(t_shell *shell, char *delim)
{
	while (shell->heredoc_input && ft_strcmp(shell->heredoc_input, delim))
	{
		if (shell->marde)
			check_dollar_in_heredoc(shell);
		ft_putstr_fd(shell->heredoc_input, shell->heredoc_fd[1]);
		ft_putchar_fd('\n', shell->heredoc_fd[1]);
		free(shell->heredoc_input);
		shell->heredoc_input = NULL;
		shell->heredoc_input = readline(">");
	}
}
