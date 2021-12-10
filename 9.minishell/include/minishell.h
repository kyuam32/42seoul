#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h> 
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "minishell_defines.h"

# define DQUOTE 34
# define SQUOTE 39
# define DUMMY	-1

/* EXECUTION INIT */
void	process_exec_several(t_order_que *order_que, char **env);
void	process_builtin_alone(t_order_que *order_que, char ***env);
void	process_execution(t_line_que *line_que, char ***env);
/* PIPE CONTROL */

void	pipe_wait(t_order_que *que);
void	pipe_stream_set(t_order_que *que);
void	pipe_make_children(char **env, t_order_que *que);
void	pipe_close_others(t_order *order);
void	pipe_children_works(char **env, t_order *curr);

/* REDIRECT CONTROL */
int		redir_enque(t_redir_que *que);
void	redir_parse(t_redir_que *que, char *type, char *path);
int		redir_in_heredocs(char *eof);
void	redir_in_set(t_order *curr, t_redir *redir);
void	redir_out_set(t_order *curr, t_redir *redir);
void	redir_set(t_order *curr);
void	redir_que_free(t_redir_que *que);

/* ARRAY CONTROL */
int		arr_len(char **arr);
char	**arr_new(char *cmd);
char	**arr_dup(char **arr);
char	**arr_add_str(char **arr, char *str);

/* ENVIRONMENT VARIABLE CONTROL */
int		get_env_key_address(char **arr, char *key); // env 문자열 시작점 반환
char	*get_env_value(char **arr, char *key);
char	*get_env_key(char *str);
char	**get_env_delete(char **arr, char *key);

/* MAKE ORDER LIST */
int		order_set(t_order_que *que_order, t_line_que *que_line, char **env);
void	order_parse(t_order *curr, char **split, char **env);
int		order_enque(t_order_que *que);
void	order_que_free(t_order_que *que);
void	order_args_parse(t_order *curr, char *cmd);
int		is_orders_fine(t_order_que *order_que, t_line_que *line_que);

/* BUILTIN COMMAND */
void	exec_builtin(t_order *curr, char ***env);
int		exec_builtin_cd(t_order *curr, char ***env);
int		exec_builtin_cd_2(t_order *curr, char ***env, char *pwd_str);
int		exec_builtin_echo(t_order *curr);
int		exec_builtin_pwd(t_order *curr);
int		exec_builtin_env(t_order *curr, char **env);
int		exec_builtin_export(t_order *curr, char ***env);
int		exec_builtin_export_2(t_order *curr, char ***env);
int		exec_builtin_unset(t_order *curr, char ***env);
int		exec_builtin_return(t_order *curr, int ret);

/* UTILS */
char	*is_executable(char *cmd, char **env);
char	*is_executable_2(char **path_token, char *cmd_str);
char	is_builtin(char *cmd);
int		is_empty_node(t_line *line);
int		is_env_format(char *str);
int		is_unset_key_format(char *str);
int		is_there_child(t_order_que *que);
void	ft_free_str(char **str);
void	ft_free_arr(char ***arr);
void	print_arr(char **arr);
int		print_errno(int err);
char	*string_to_lower(char *string);
int		is_redir(char *str);

/* dongklee */
char	*env_to_str(char *env, int dummy, int is_dquote);

int		tokenizer_line(t_line_que *line, char *buf);
int		split_pipe_line(t_line_que *line, char *buf, int start, int end);
int		next_pipe_line(t_line_que *line);
int		init_line(t_line_que *line);
int		skip_quotes(char *buf, int *i, int *is_quote);
int		skip_squote(char *buf, int *i, int *is_quote);
int		split_cmd_line(t_line_que *line);
int		convert_dummy(t_line_que *line);
int		convert_dummy_quotes(t_line *origin, int *i, int *is_quote, int quote);
int		convert_dummy_back(t_line_que *line);
int		trim_splited_word(t_line_que *line);
int		trim_splited_word_quotes(t_line *origin, int i);
int		trim_quotes(t_line *origin, int i, int *j, char quote);
int		init_quote(t_quote *quote);
int		interpolate_dollar_sign(t_line_que *line);
int		interpolate_dollar_sign_sub(t_line *origin, int *i, int *is_dquote);
int		interpolate_tilde_sign(t_line_que *line);
int		convert_tilde_to_home(t_line *origin, int i, int j);
int		interpolate_redirection_blank(t_line_que *line);
int		ft_is_redirection(char *cmd_line, int i);
int		put_buffer(t_line *line, int *i);
int		put_buffer_blank(t_line *line, int i);
int		interpolate_env_var(t_line *origin, char *env, int origin_i);
int		ft_is_special_char(char c);
void	print_cmd_line(t_line_que *line);
void	print_splited_line(t_line_que *line);

int		splited_cmd_count(t_line_que *line);

int		release_all_nodes(t_line_que *line);

int		exception_handler(char *buf);
int		exception_unclosed_quotes(char *buf);
int		exception_only_space(char *buf);
int		exception_invalid_redirection(char *buf);
int		ft_error_exit_syntax(char *inter);
int		exception_redir_with_no_path(t_line_que *line);
int		ft_quoted_redirection(char *splited, int suspicious);

int		ft_original_redirection(char *splited);
int		put_buffer_redirection(t_line *origin, int i);

void	exec_prompt(t_line_que *line);

void	set_terminal(struct termios *set_term);
void	signal_handler(void);
void	signal_interrupt(int signo);
void	signal_quit(int signo);
void	eof_exit(void);

char	*ft_str_init_env(t_line *origin, char *env);
char	*ft_str_init(int res_len);

void	interpolate_env_var_sub(t_line *origin, char *res, char *env, int ori);
int		tokenizer_line_sub(t_line_que *line, char *buf, int *pipe_idx, int i);

void	trim_quotes_sub(int *flag, int *tmp_j, int *res_j);
void	init_trim_func_args(int *res_idx, int *res_j, int *tmp_j, int *flag);

char	*env_value_in_dquote(char *str);
int		env_word_len_with_blank(char *str);
void	ft_is_dquote(char cmd_line, int *is_dquote);

#endif
