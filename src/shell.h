/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:35:06 by slord             #+#    #+#             */
/*   Updated: 2023/01/28 23:21:41 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h> 
# include <errno.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char			**token;
	char			***cmds;
	char			**cmds_exe;
	char			**env;
	char			**path;
	int				nb_cmds;
	char			*buffer;
	char			**pre_command;
	int				*fd;
	int				*id;
	char			**temp;
	int				status;
	int 			index;
	char 			*variable;
	char			*heredoc_input;
}		t_shell;



void	get_path(t_shell *info);
void	launch_terminal(t_shell *info);
void	separate_input(t_shell *info);
void	separate_cmds(t_shell *info);
void	modify_command(t_shell *info, int i);
void	execute(t_shell *info);
void	count_cmds(t_shell *shell);
char 	***lexer1(char *buffer, t_shell *shell);
void	free_cmds(t_shell *shell);
int 	set_pipes(t_shell *shell);
void	change_in_and_out(t_shell *shell, int i);
int		check_built_in(t_shell *shell, int i);
int		pwd(t_shell *shell, char **cmds,int i);
int		env(t_shell *shell);
int		check_redirection(t_shell *shell, int i);
int		check_input(t_shell *shell, int i);
void	duplicate_cmds(t_shell *shell);
void	supress_operators(t_shell *shell, int i);
int		echo(t_shell *shell, char **cmds, int i);
void	signals(int i);
t_shell	*get_struc(void);
void	check_vars(char *cmd, t_shell *shell);
void	modify_env(t_shell *shell, char *str);
int		export(t_shell *shell, char **cmds);
void	check_built_in_parent(t_shell *shell);
int 	check_var(t_shell *shell, char *var);
void	modify_env_1(t_shell *shell, int i);
int		unset(t_shell *shell, char **cmds);
int 	count_nb_cmds(char ***cmds);
void	heredoc(t_shell *shell, char *cmd, int i);
void	check_dollar_in_command(t_shell *shell, int i, char **cmd);
void	check_quotes(t_shell *shell, int i, int j);
void	exit_built_in(t_shell *shell);
void	close_fd(void);
void	check_if_variable_exist(t_shell *shell, char *var);
void	ft_strcpy(char *dst, const char *src);
void	check_dollar_in_heredoc(t_shell *shell, char *heredoc);

#endif