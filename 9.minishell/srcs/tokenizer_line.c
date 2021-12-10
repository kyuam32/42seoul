#include "minishell.h"

int	tokenizer_line(t_line_que *line, char *buf)
{
	int			is_quote;
	int			pipe_idx;
	int			i;

	init_line(line);
	pipe_idx = 0;
	i = -1;
	while (buf[++i])
	{
		is_quote = 0;
		if (skip_quotes(buf, &i, &is_quote) == 1)
			return (0);
		if (tokenizer_line_sub(line, buf, &pipe_idx, i) == 1)
			return (0);
	}
	if (pipe_idx < i)
		split_pipe_line(line, buf, pipe_idx, i);
	split_cmd_line(line);
	return (0);
}

int	tokenizer_line_sub(t_line_que *line, char *buf, int *pipe_idx, int i)
{
	if (buf[i] == '|' && buf[i + 1])
	{
		split_pipe_line(line, buf, (*pipe_idx), i);
		(*pipe_idx) = i + 1;
	}
	else if (buf[i] == '|' && buf[i + 1] == '\0')
	{
		split_pipe_line(line, buf, (*pipe_idx), i);
		next_pipe_line(line);
		split_cmd_line(line);
		return (1);
	}
	return (0);
}

int	split_cmd_line(t_line_que *line)
{
	t_line	*origin;
	int		i;

	while (line->head->prev != NULL)
		line->head = line->head->prev;
	interpolate_dollar_sign(line);
	convert_dummy(line);
	interpolate_redirection_blank(line);
	origin = line->head;
	i = 0;
	while (origin)
	{
		origin->splited = ft_split(origin->cmd_line, ' ');
		origin = origin->next;
	}
	convert_dummy_back(line);
	interpolate_tilde_sign(line);
	trim_splited_word(line);
	return (0);
}
