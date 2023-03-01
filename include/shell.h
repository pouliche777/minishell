/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:35:06 by slord             #+#    #+#             */
/*   Updated: 2023/03/01 12:43:56 by bperron          ###   ########.fr       */
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
# include "../readline/readline.h"
# include "../readline/history.h"
# include "sys/ioctl.h"
# include "sys/wait.h"

typedef struct s_shell
{
	char	**token;
	char	***cmds;
	char	**cmds_exe;
	char	**env;
	char	**path;
	char	**pre_command;
	char	**temp;
	char	*buffer;
	char	*var_name;
	char	*hold;
	char	*var;
	char	*variable;
	char	*heredoc_input;
	int		*fd;
	int		*id;
	int		heredoc_fd[2];
	int		nb_cmds;
	int		status;
	int		index;
	int		last_var;
	int		marde;
	int		terminal;
	int		error;
}		t_shell;

//built_in_utils.c
int		check_built_in(t_shell *shell, int i);
int		pwd(t_shell *shell);
int		env(t_shell *shell);
void	check_built_in_parent(t_shell *shell, int i);

//built_in.c
int		unset(t_shell *shell, char *cmds);
int		export(t_shell *shell, char **cmds);
char	*get_pwd(char **env);
int		cd_built_in(t_shell *shell, char *path);

//change_var_utils.c
int		redir_check(char *cmd, int i);
int		end_while(t_shell *shell, int i, int j);
int		find_var_len(t_shell *shell, int env_place);
int		put_new_var(t_shell *shell, char *new, int var_place, int env_place);

//change_var.c
void	loop_var(t_shell *shell, int i, int doubles, int singles);
void	status(t_shell *shell, int i, int j, int k);
void	find_var(t_shell *shell, int i);
void	remove_var(t_shell *shell, int var_place, int size);
void	change_var(t_shell *shell, int var_place, int env_place, int len);

//echo.c
void	echo(char **cmds);
int		check2(char **cmd, int row);
int		check_flags(char **cmd, int *row);
void	print(char **cmd, int row);

//env_1.c
void	init_env(t_shell *shell, char **env);
void	delete_env(t_shell *shell, char *var_name);

//env.c
void	add_env(t_shell *shell, char *var_line, int i, char **cmd);
void	get_var(t_shell *shell, char *var_line);
void	replace_var_1(t_shell *shell, char *var_line);
int		check_if_var_exist(t_shell *shell);

//execute_utils.c
int		count_nb_tokens(char **cmd);
int		modify_command(t_shell *info, int i, char *str, char *ptr);
void	supress_operators(t_shell *shell, int i);

//execute.c
void	execute(t_shell *info);
void	get_return_value(t_shell *shell);
void	children(t_shell *shell, int i);

//exit.c
int		check_arg(char *arg);
void	set_status(char *arg, unsigned char *status);
void	exit_built_in(t_shell *shell, char **exit_arg);

//heredoc.c
void	check_heredoc_parent(t_shell *shell, int i);
void	check_dollar_in_heredoc(t_shell *shell);
void	heredoc(t_shell *shell, char *cmd);
void	heredoc_variable(t_shell *shell, int j, int h, int i);

//lexer.c
void	lexer(char *buffer, t_shell *shell, int i, int j);
int		is_space(char *cmd);
void	parsing(int row, t_shell *shell);

//minishell.c
void	launch_terminal(t_shell *info);
t_shell	*get_struc(void);

//parsing.c
void	separate_input(t_shell *info);
void	count_cmds(t_shell *shell);
void	separate_cmds(t_shell *info);
int		skip_quote(char *buffer, char c, t_shell *info);

//pipes.c
int		set_pipes(t_shell *shell);
void	change_in_and_out(t_shell *shell, int i);

//quotes.c
int		count_nb_quotes(char *str);
void	suppress_quotes(t_shell *shell, char *temp, int i);
void	check_quotes(t_shell *shell);

//redir_utils.c
int		find_size(t_shell *shell, int i, int doubles, int singles);
int		count_redir(t_shell *shell, int singles, int doubles);

//redir.c
void	is_good(char *cmd, t_shell *shell, int i);
void	is_good_1(char **cmds, t_shell *shell);
void	check_redir(t_shell *shell, int row);

//redirection.c
int		check_output(t_shell *shell, int i);
int		check_input(t_shell *shell, int i);
void	redirect_output_1(char *cmd);
void	redirect_output(char *cmd);
void	redirect_input(char *cmd);

//signals.c
void	sighandlerc(int signum);
void	sighush(int signum);
void	sigheredoc(int signum);
void	sigheredoc2(int signum);
void	signal_handling(void);

//spaces.c
char	*rm_spaces(char *cmd, int len, int singles, int doubles);
char	*space_quotes(char *cmd, int doubles, int singles, int i);
char	*remove_spaces(char *cmd);
void	trim(t_shell *shell, int row);

//split_args.c
int		count_args(char **cmd, int nb);
int		find_arg_size(char *cmd, int start);
void	split_args(t_shell *shell, int row, int i, int j);
int		cmd_lenght(char *cmd, int start);
char	**split_pipe(char *cmd, int nb);

//utils.c
void	get_path(t_shell *info);
int		count_nb_cmds(char ***cmds);
int		count_nb_token(char **cmds);
void	free_env(t_shell *shell);

//utils2.c
int		arr_size(char **arr);
void	free_arrarrarr(char ***arr);
void	free_garbage(t_shell *shell, unsigned char status);
void	close_fds(t_shell *shell);
void	check_open_files(t_shell *shell, int i);

//variables.c
void	ft_strcpy(char *dst, const char *src);
int		check_v(t_shell *shell, char *var);

#endif