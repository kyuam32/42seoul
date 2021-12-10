#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

# define TRUE 1
# define FALSE 0

# define CHILD 0
# define PARENT 1

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define FD_READ 0
# define FD_WRITE 1

/* REDIRECT DEFINES  */
# define REDIR_IN	1
# define REDIR_OUT	2
# define REDIR_APP	3
# define REDIR_HERE_DOC	4

/* BUILTIN DEFINES */
# define B_ECHO		1
# define B_CD		2
# define B_PWD		3
# define B_EXPORT	4
# define B_UNSET	5
# define B_ENV		6
# define B_EXIT		7

typedef struct s_stream
{
	pid_t	pid;
	int		fd[2];
	int		pipe_w;
	int		pipe_r;
}			t_stream;

typedef struct s_redir
{
	char				type;
	char				*path;
	struct s_redir		*next;
	struct s_redir		*prev;
}						t_redir;

typedef struct s_redir_que
{
	t_redir		*head;
	t_redir		*tail;
	int			size;
}				t_redir_que;

typedef struct s_order
{
	char			builtin;
	char			*path;
	char			**args;
	t_redir_que		redir_que;
	t_stream		stream;
	struct s_order	*next;
	struct s_order	*prev;
}					t_order;

typedef struct s_order_que
{
	t_order	*head;
	t_order	*tail;
	int		size;
}			t_order_que;

typedef struct s_line
{
	char			*cmd_line;
	char			**splited;
	struct s_line	*prev;
	struct s_line	*next;
}					t_line;

typedef struct s_line_que
{
	t_line		*head;
	int			size;
}				t_line_que;

typedef struct s_quote
{
	char		s[2];
	char		d[2];
}				t_quote;

typedef struct s_state
{
	t_order_que	order_que;
	int			exit_status;
	int			is_child;
	int			signal_flag;
	int			process_flag;
	char		**local_envp;
}				t_state;

t_state	g_state;

#endif