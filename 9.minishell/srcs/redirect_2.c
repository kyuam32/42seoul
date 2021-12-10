#include "minishell.h"

void	redir_que_free(t_redir_que *que)
{
	t_redir	*curr;
	t_redir	*temp;

	if (!que)
		return ;
	curr = que->head;
	while (curr)
	{
		ft_free_str(&curr->path);
		temp = curr;
		curr = curr->next;
		ft_memset(temp, 0, sizeof(t_redir));
		free(temp);
	}
	ft_memset(que, 0, sizeof(t_redir_que));
}

int	redir_enque(t_redir_que *que)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!(new))
		print_errno(errno);
	ft_memset(new, 0, sizeof(t_redir));
	if (que->tail == NULL)
	{
		new->next = NULL;
		que->head = new;
	}
	else
	{
		new->prev = que->tail;
		que->tail->next = new;
	}
	new->next = NULL;
	que->tail = new;
	que->size++;
	return (0);
}

void	redir_parse(t_redir_que *que, char *type, char *path)
{
	redir_enque(que);
	if (!(ft_strcmp(type, "'>")))
		que->tail->type = REDIR_OUT;
	else if (!(ft_strcmp(type, "'>>")))
		que->tail->type = REDIR_APP;
	else if (!(ft_strcmp(type, "'<")))
		que->tail->type = REDIR_IN;
	else if (!(ft_strcmp(type, "'<<")))
		que->tail->type = REDIR_HERE_DOC;
	que->tail->path = ft_strdup(path);
}

void	heredocs(char *eof, int *fd)
{
	char	*line;

	g_state.is_child = TRUE;
	close(fd[FD_READ]);
	write(STD_OUT, "> ", 2);
	while (get_next_line(STD_IN, &line) > 0 && !g_state.signal_flag)
	{
		if (!(ft_strcmp(line, eof)))
			break ;
		write(STD_OUT, "> ", 2);
		write(fd[FD_WRITE], line, ft_strlen(line));
		write(fd[FD_WRITE], "\n", 1);
	}
	exit (0);
}

int	redir_in_heredocs(char *eof)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == CHILD)
		heredocs(eof, fd);
	else
	{
		g_state.is_child = FALSE;
		close(fd[FD_WRITE]);
		waitpid(pid, &status, 0);
	}
	return (fd[FD_READ]);
}
