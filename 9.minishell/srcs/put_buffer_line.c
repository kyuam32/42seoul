#include "minishell.h"

int	put_buffer_blank(t_line *line, int i)
{
	char	*res;
	int		res_len;
	int		res_idx;
	int		cmd_idx;

	res_len = ft_strlen(line->cmd_line) + 1 + 1;
	res = (char *)malloc(sizeof(char) * res_len);
	if (res == NULL)
		return (0);
	res_idx = 0;
	cmd_idx = 0;
	while (res_idx < res_len && line->cmd_line[cmd_idx])
	{
		if (res_idx == i)
			res[res_idx++] = ' ';
		res[res_idx++] = line->cmd_line[cmd_idx++];
	}
	res[res_idx] = '\0';
	free(line->cmd_line);
	line->cmd_line = res;
	return (0);
}

int	put_buffer(t_line *line, int *i)
{
	if ((*i) > 0)
		if ((line->cmd_line[(*i) - 1] != ' ') && \
		(line->cmd_line[(*i) - 1] != '>' || line->cmd_line[(*i) - 1] != '<'))
			put_buffer_blank(line, (*i));
	while (line->cmd_line[(*i)] && (line->cmd_line[(*i)] == '>' \
												|| line->cmd_line[(*i)] == '<'))
		(*i)++;
	if (line->cmd_line[(*i)] != ' ' && line->cmd_line[(*i)])
		put_buffer_blank(line, (*i));
	return (0);
}

int	put_buffer_redirection(t_line *origin, int i)
{
	char	*res;

	if (origin->splited[i][0] == (char)SQUOTE)
		return (0);
	res = ft_strjoin("'", origin->splited[i]);
	free(origin->splited[i]);
	origin->splited[i] = res;
	return (0);
}

int	trim_splited_word(t_line_que *line)
{
	t_line	*origin;
	t_quote	quote;
	int		i;

	origin = line->head;
	init_quote(&quote);
	while (origin)
	{
		i = 0;
		while (origin->splited[i])
		{
			if (ft_original_redirection(origin->splited[i]))
				put_buffer_redirection(origin, i);
			else
				trim_splited_word_quotes(origin, i);
			i++;
		}
		origin = origin->next;
	}
	return (0);
}

int	trim_splited_word_quotes(t_line *origin, int i)
{
	int		j;
	int		tmp_j;

	tmp_j = 0;
	j = 0;
	while (origin->splited[i][j])
	{	
		if (origin->splited[i][j] == DQUOTE)
		{
			tmp_j = trim_quotes(origin, i, &j, DQUOTE);
			j = tmp_j;
		}
		else if (origin->splited[i][j] == SQUOTE)
		{
			tmp_j = trim_quotes(origin, i, &j, SQUOTE);
			j = tmp_j;
		}
		j++;
	}
	return (0);
}
