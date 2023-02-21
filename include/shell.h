/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:35:06 by slord             #+#    #+#             */
/*   Updated: 2023/02/21 11:02:43 by bperron          ###   ########.fr       */
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
# include "readline/readline.h"
# include "readline/history.h"
# include "sys/ioctl.h"

typedef struct s_shell
{
	char			**token;
	char			***cmds;
	char			**cmds_exe;
	char			**env;
	char			**path;
	int				nb_cmds;
	char			*buffer;
	char			*hold;
	char			**pre_command;
	int				*fd;
	int				*id;
	char			**temp;
	char			*var_name;
	char			*var;
	int				status;
	int 			index;
	char 			*variable;
	char			*heredoc_input;
	int				heredoc_fd[2];
	int				last_var;
}		t_shell;


int		ft_strcmp(char *s1, char *s2);
void	get_path(t_shell *info);
void	launch_terminal(t_shell *info);
void	separate_input(t_shell *info);
void	separate_cmds(t_shell *info);
int		modify_command(t_shell *info);
void	init_env(t_shell *shell, char **env);
void	execute(t_shell *info);
void	count_cmds(t_shell *shell);
void 	lexer(char *buffer, t_shell *shell);
void	free_cmds(t_shell *shell);
int 	set_pipes(t_shell *shell);
void	change_in_and_out(t_shell *shell, int i);
int		check_built_in(t_shell *shell, int i);
int		pwd(t_shell *shell, int i);
int		env(t_shell *shell);
int		check_output(t_shell *shell, int i);
int		check_input(t_shell *shell, int i);
void	duplicate_cmds(t_shell *shell);
void	supress_operators(t_shell *shell, int i);
int		echo(char **cmds);
t_shell	*get_struc(void);
void	check_vars(char *cmd, t_shell *shell);
void	modify_env(t_shell *shell, char *str);
int		export(t_shell *shell, char **cmds);
void	check_built_in_parent(t_shell *shell, int i);
int		unset(t_shell *shell, char *cmds);
int 	count_nb_cmds(char ***cmds);
void	heredoc(t_shell *shell, char *cmd);
void	check_dollar_in_command(t_shell *shell, int i, char **cmd);
void	check_quotes(t_shell *shell);
void	exit_built_in(t_shell *shell, char *exit_arg);
void	close_fd(void);
int		check_v(t_shell *shell, char *var);
void	ft_strcpy(char *dst, const char *src);
void	check_dollar_in_heredoc(t_shell *shell);
void	replace_var(t_shell *shell, char *var);
int		count_nb_token(char **cmds);
void	check_heredoc_parent(t_shell *shell, int i);
int		cd_built_in(t_shell *shell, char *path);
char	*get_pwd(char **env);
void	add_env(t_shell *shell, char *var_line, int j);
void	delete_env(t_shell *shell, char *var_name);
void	free_env(t_shell *shell);

//spaces.c
char	*rm_spaces(char *cmd, int len, int singles, int doubles);
int		quotes_error(int singles, int doubles);
char	*space_quotes(char *cmd, int doubles, int singles, int i);
char	*remove_spaces(char *cmd);
void	trim(t_shell *shell, int row);

//change_var.c
void	loop_var(t_shell *shell, int i, int doubles, int singles);
void	status(t_shell *shell, int i, int j, int k);
void	find_var(t_shell *shell, int i);
void	remove_var(t_shell *shell, int var_place, int size);
void	change_var(t_shell *shell, int var_place, int env_place, int len);

//change_var_utils.c
int		redir_check(char *cmd, int i);
int		end_while(t_shell *shell, int i, int j);
int		find_var_len(t_shell *shell, int env_place);
int		put_new_var(t_shell *shell, char *new, int var_place, int env_place);

//redir.c
int		count_redir(t_shell *shell, int singles, int doubles);
int		find_size(t_shell *shell, int i, int doubles, int singles);
void	check_redir(t_shell *shell, int row);

//split_args.c
int		count_args(char **cmd, int nb);
int		find_arg_size(char *cmd, int start);
void	split_args(t_shell *shell, int row, int i, int j);
int		cmd_lenght(char *cmd, int start);
char	**split_pipe(char *cmd, int nb);

//signals.c
void	sighandlerc(int signum);
void	sighush(int signum);
void	sigheredoc(int signum);
void	sigheredoc2(int signum);
void	signal_handling(void);

//utils2.c
int		arr_size(char **arr);

#endif