#include "minishell.h"

void	pipe_close_others(t_order *order)
{
	t_order	*curr;

	curr = order->prev;
	while (curr)
	{
		if (curr->stream.pipe_r > 2)
			close(curr->stream.pipe_r);
		if (curr->stream.pipe_w > 2)
			close(curr->stream.pipe_w);
		curr = curr->prev;
	}
	curr = order->next;
	while (curr)
	{
		if (curr->stream.pipe_r > 2)
			close(curr->stream.pipe_r);
		if (curr->stream.pipe_w > 2)
			close(curr->stream.pipe_w);
		curr = curr->next;
	}
}

void	pipe_make_children(char **env, t_order_que *que)
{
	t_order	*curr;

	curr = que->head;
	while (curr)
	{
		curr->stream.pid = fork();
		if (curr->stream.pid == -1)
			print_errno(errno);
		if (curr->stream.pid == CHILD)
			pipe_children_works(env, curr);
		else
		{
			g_state.is_child = FALSE;
			if (curr->stream.pipe_r > 2)
				close(curr->stream.pipe_r);
			if (curr->stream.pipe_w > 2)
				close(curr->stream.pipe_w);
		}
		curr = curr->next;
	}
}

void	pipe_children_works(char **env, t_order *curr)
{
	g_state.is_child = TRUE;
	pipe_close_others(curr);
	if (!curr->path && !curr->builtin)
		exit (1);
	if (curr->stream.pipe_r)
		dup2(curr->stream.pipe_r, STD_IN);
	if (curr->stream.pipe_w)
		dup2(curr->stream.pipe_w, STD_OUT);
	if (curr->builtin)
		exec_builtin(curr, &env);
	else
		execve(curr->path, curr->args, env);
}

void	pipe_stream_set(t_order_que *que)
{
	t_order	*curr;

	curr = que->head;
	while (curr->next)
	{
		pipe(curr->stream.fd);
		curr->stream.pipe_w = curr->stream.fd[FD_WRITE];
		curr->next->stream.pipe_r = curr->stream.fd[FD_READ];
		curr = curr->next;
	}
	curr = que->head;
	while (curr)
	{
		if (curr->redir_que.head)
			redir_set(curr);
		curr = curr->next;
	}
}

void	pipe_wait(t_order_que *que)
{
	t_order	*curr;
	int		status;
	int		sig_term;
	int		non_sig_term;

	curr = que->head;
	non_sig_term = -1;
	while (curr)
	{
		if (curr->stream.pid)
		{
			wait(&status);
			if (WIFSIGNALED(status))
				sig_term = WTERMSIG(status) + 128;
			else
				non_sig_term = WEXITSTATUS(status);
		}
		curr = curr->next;
	}
	if (non_sig_term == -1)
		g_state.exit_status = sig_term;
	else
		g_state.exit_status = non_sig_term;
}
