/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:39:13 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 12:16:06 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <limits.h>

# define MAX_FD 10240
# define BUFFER_SIZE 1024
# define SHELLNAME "minishell"
# define ERRSH "No options or arguments allowed.\nUsage: $ ./minishell"

//this structure gets the line from readline in line.line
//splits the line in an array of string line.commands
//based on the | and expands the $variables

typedef struct s_line
{
	char		*line;
	char		**commands;
	int			tmp_v;
}				t_line;

//this structure gets from the line.commands each command, then
//puts the redirections in the variables, splits the command
//based on whitespaces and removes the quotes

typedef struct s_each
{
	char	**cmmd;
	char	**env;
	int		pipes;
	int		max_pipes;
	int		r_i;
	int		r_o;
	int		r_ii;
	int		r_oo;
	char	*i_file;
	char	*ii_file;
	char	*o_file;
	int		lst_red;
}				t_each;

typedef struct s_pipes
{
	int		**pipes;
	int		*pid;
}				t_pipes;

typedef struct s_status
{
	int		max;
	int		built;
	int		v_exit;
	int		w_status;
	int		fd_in;
	int		fd_out;
	t_pipes	*pipes;
	char	**envp_2;
	t_list	*sh_env;
	int		fd_stdout;
}				t_status;

t_list	*env_init(char *envp[]);
int		env_env(t_list *sh_env, char *cmd[], int fd);
int		cd(t_list **sh_env, char **cmd);
int		pwd(int fd, char **cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_arrlen(char **arr);
int		echo(char **cmd, int fd, t_status *sh, t_each *elem);
int		env_export(t_list **sh_env, char *cmd[]);
int		env_unset(t_list **sh_env, char *cmd[]);
void	exit_shell(t_list **sh_env, int exit_no, t_each ***c);
int		exit_cmd(t_list **sh_env, char *cmd[], t_each ***c, int v_exit);
char	*env_set_value(t_list **sh_env, char *varstr);
void	handle_sigint_rl(int signum);
void	handle_sigint_parent(int signum);
void	handle_sigquit_parent(int signum);
char	**ft_lst2arr(t_list *lst);
int		chk_inval_opt(char **cmd);
int		ft_is_bashname(char *name);
void	env_print(t_list *sh_env, int fd);
char	*ft_get_key(char *str, char separator);
int		errmsg(char *cmdname, char *cmdarg, char *errmsg, int errcode);
int		ft_isstrnum(char *str);

//split_commands_1.c

int		ft_split_line(char *line_read, char ***commands);

//manage_commands_1.c

int		ft_expand_var(t_line *line, t_status *sh);

//manage_commands_2.c

int		ft_find_char(char *str, char c);
int		ft_extract_options(char *str);

//manage_commands>3.c

char	*ft_extract_command(char *str);
void	ft_init_structure(t_each *var);
char	*ft_variable(char *var, char *envp[], int v_exit);
int		ft_find_dolar(char *str, int *in_quotes);
int		ft_is_shell(char c);

//libft_helpers_1.c

char	*ft_substr_f(char const *s, unsigned int start, size_t len);

//libft_helpers_2.c

char	*ft_strjoin_ch(char const *s1, char c);
char	**ft_split_f(char const *s, char c);

//helpers_functions_1.c

int		ft_is_whitespace(char c);
void	ft_remove_ws(char **str);
void	ft_free(char **str);

//ft_devide_commands.c

t_each	*ft_devide_comm(char **str, char **envp_2);

//ft_devide_command_1.c

char	**ft_split_command(char *str);
void	ft_remove_quotes(char **str);

//ft_devide_command_2.c

int		ft_com_size(char *str);
void	ft_cut_string(char **str, int start, int end);
int		ft_len(char *str);
char	*ft_return_position(char *str, char c);

//ft_devide_command_3.c

int		ft_set_size_oo(int *start, t_each *ret, char **str, int c);
int		ft_set_size_ii(int *start, t_each *ret, char **str, int c);
void	ft_heredoc_redirect(char **str, t_each *ret, int *size, int *start);

//test_paths_1.c

int		ft_check_path(char **cmmd, char *envp[]);
char	*ft_get_path(char *cmd, char *envp[]);
char	**ft_return_path(char *envp[]);

//manage_pipes_1.c

void	ft_execute(t_each **c, int i);

//pipes_helpers_1.c

void	ft_get_lines(char *limiter, t_status *sh, t_each **c);
void	ft_gnl_built(char *limiter);

//fd_handle_1.c

void	ft_modify_fd(t_each **elem, t_status *sh, int i);
int		ft_modify_fd_2(t_each *elem, int *fd_in, int *fd_out);
int		ft_test_file(char *str, int type);

//get_next_line.c

char	*get_next_line(int fd);

//error_helpers_1.c

void	ft_file_error(char *file, t_each **c, t_status *sh);
void	ft_file_error_no_exit(char *file, t_status *sh);
void	ft_pipe_fork_error(char c);
void	ft_cmd_error(t_each **c, int i);
void	ft_error(int fd);

//free_helpers.c

void	ft_free_db_array(char **str);
void	ft_free_double(char ***str);
void	ft_free_full_struct(t_each ***elem);
void	ft_free_gnl(char **val);

//free_helpers_1.c

void	ft_free_pipes(t_pipes **pipes, int size);

//check_builtsin.c

int		ft_is_builtin(char *str);
int		ft_return_built(int i, t_status *sh, t_each *elem, t_each ***c);

//conversion_helpers.c

char	**ft_copy_array(char **str);
int		ft_check_pipe_error(char *str);
int		ft_check_quotes(char *str);

//ft_pipes_utils.c

t_pipes	*ft_create_pipes(int size);
void	ft_pipes_2(t_each **elem, t_list **env_sh, t_pipes *pipes, int pid);
void	ft_close_all_pipes(int **pipes, int size);
void	ft_close_pipes(int **pipes, int size, int index);

//struct_helpers.c

void	ft_sh_init(t_status *sh, char *envp[]);

//parse_helpers.c

int		ft_check_line(t_line *line, t_status *sh, t_each ***c);
void	ft_create_cmds(t_line *line, t_each ***c, t_status *sh);
void	ft_line_fail(t_line *line, t_status *sh);

//exec_helpers.c

int		ft_exec_built_in(t_status *sh, t_each **c);
void	ft_fd_handle(t_status *sh, t_each **c, int i);
void	ft_exec_pipe(t_each **c, t_status *sh, int i);

//exec_helpers2.c

void	ft_parent_proc(t_status *sh, t_each **c, int i);
void	ft_pipeline(t_status *sh, t_each **c);
void	ft_built_redir(t_status *sh, t_each **c);
void	ft_execute_command(t_each **c, t_status *sh, int i);

#endif