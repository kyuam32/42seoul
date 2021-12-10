#include "minishell.h"

void	redir_in_set(t_order *curr, t_redir *redir)
{
	int	fd_in;

	fd_in = 0;
	if (redir->type == REDIR_IN)
		fd_in = open(redir->path, O_RDONLY, 0644);
	else if (redir->type == REDIR_HERE_DOC)
		fd_in = redir_in_heredocs(redir->path);
	if (fd_in < 0)
	{
		print_errno(errno);
		return ;
	}
	if (curr->builtin || curr->path)
		curr->stream.pipe_r = fd_in;
}

void	redir_out_set(t_order *curr, t_redir *redir)
{
	int	fd_out;

	fd_out = 0;
	if (redir->type == REDIR_OUT)
		fd_out = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APP)
		fd_out = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		print_errno(errno);
		return ;
	}
	if (curr->builtin || curr->path)
		curr->stream.pipe_w = fd_out;
}

void	redir_set(t_order *curr)
{
	t_redir	*redir;

	redir = curr->redir_que.head;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HERE_DOC)
			redir_in_set(curr, redir);
		else
			redir_out_set(curr, redir);
		redir = redir->next;
	}
}
