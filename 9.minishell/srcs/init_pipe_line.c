#include "minishell.h"

int	split_pipe_line(t_line_que *line, char *buf, int start, int end)
{
	t_line	*before;

	before = line->head;
	if (line->head->cmd_line == NULL)
		line->head->cmd_line = ft_substr(buf, start, (end - start));
	else if (line->head->cmd_line != NULL)
	{
		line->head->next = (t_line *)malloc(sizeof(t_line));
		if (line->head == NULL)
			return (0);
		line->head = line->head->next;
		line->head->cmd_line = ft_substr(buf, start, (end - start));
		line->head->splited = NULL;
		line->head->prev = before;
		line->head->next = NULL;
	}
	line->size += 1;
	return (0);
}

int	next_pipe_line(t_line_que *line)
{
	t_line	*before;

	before = line->head;
	if (line->head->cmd_line != NULL)
	{
		line->head->next = (t_line *)malloc(sizeof(t_line));
		if (line->head == NULL)
			return (0);
		line->head = line->head->next;
		line->head->cmd_line = ft_strdup("");
		line->head->splited = NULL;
		line->head->prev = before;
		line->head->next = NULL;
	}
	line->size += 1;
	return (0);
}

int	init_line(t_line_que *line)
{
	line->size = 0;
	line->head = (t_line *)malloc(sizeof(t_line));
	if (line->head == NULL)
		return (0);
	line->head->prev = NULL;
	line->head->next = NULL;
	line->head->cmd_line = NULL;
	line->head->splited = NULL;
	return (0);
}

int	release_all_nodes(t_line_que *line)
{
	t_line	*tmp;
	t_line	*tmp_next;
	int		idx;

	tmp = line->head;
	if (tmp == NULL)
		return (0);
	idx = 0;
	while (idx < line->size)
	{
		ft_free_arr(&tmp->splited);
		ft_free_str(&tmp->cmd_line);
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_next;
		if (tmp == line->head)
			return (0);
		idx++;
	}
	return (0);
}

int	init_quote(t_quote *quote)
{
	quote->s[0] = SQUOTE;
	quote->s[1] = '\0';
	quote->d[0] = DQUOTE;
	quote->d[1] = '\0';
	return (0);
}
