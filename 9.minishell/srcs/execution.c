#include "minishell.h"

void	just_exit(void)
{
	printf("exit");
	exit(0);
}

int	can_i_init_process(void)
{
	if (g_state.signal_flag || g_state.exit_status)
	{
		if (g_state.signal_flag)
			g_state.exit_status = g_state.signal_flag;
		return (FALSE);
	}
	return (TRUE);
}

void	process_exec_several(t_order_que *order_que, char **env)
{
	if (can_i_init_process() == FALSE)
		return ;
	pipe_make_children(env, order_que);
	pipe_wait(order_que);
}

void	process_builtin_alone(t_order_que *order_que, char ***env)
{
	int	copy_stdin;
	int	copy_stdout;

	if (can_i_init_process() == FALSE)
		return ;
	copy_stdin = dup(STD_IN);
	copy_stdout = dup(STD_OUT);
	if (order_que->head->stream.pipe_r > 2)
		dup2(order_que->head->stream.pipe_r, STD_IN);
	if (order_que->head->stream.pipe_w > 2)
		dup2(order_que->head->stream.pipe_w, STD_OUT);
	order_que->head->stream.pid = PARENT;
	exec_builtin(order_que->head, env);
	dup2(copy_stdin, STD_IN);
	dup2(copy_stdout, STD_OUT);
}

void	process_execution(t_line_que *line_que, char ***env)
{
	g_state.exit_status = EXIT_SUCCESS;
	g_state.signal_flag = FALSE;
	g_state.process_flag = TRUE;
	if (order_set(&g_state.order_que, line_que, *env) == EXIT_SUCCESS)
	{
		if (line_que->size)
		{
			pipe_stream_set(&g_state.order_que);
			is_orders_fine(&g_state.order_que, line_que);
			if (g_state.order_que.size == 1 && \
				g_state.order_que.head->builtin == B_EXIT)
				just_exit();
			else if (g_state.order_que.size == 1 && \
					g_state.order_que.head->builtin)
				process_builtin_alone(&g_state.order_que, env);
			else
				process_exec_several(&g_state.order_que, *env);
		}
	}
	order_que_free(&g_state.order_que);
	g_state.process_flag = FALSE;
}
