#include "minishell.h"

int	convert_dummy_back(t_line_que *line)
{
	t_line	*origin;
	int		i;
	int		j;

	origin = line->head;
	while (origin)
	{
		i = -1;
		while (origin->splited[++i])
		{
			j = -1;
			while (origin->splited[i][++j])
				if (origin->splited[i][j] == DUMMY)
					origin->splited[i][j] = ' ';
		}
		origin = origin->next;
	}
	return (0);
}

int	convert_dummy(t_line_que *line)
{
	t_line	*origin;
	int		i;
	int		is_quote;

	origin = line->head;
	while (origin)
	{
		i = -1;
		while (origin->cmd_line[++i])
		{
			is_quote = 0;
			if (origin->cmd_line[i] == DQUOTE)
			{
				if (convert_dummy_quotes(origin, &i, &is_quote, DQUOTE) == 1)
					return (1);
			}
			else if (origin->cmd_line[i] == SQUOTE)
				if (convert_dummy_quotes(origin, &i, &is_quote, SQUOTE) == 1)
					return (1);
		}
		origin = origin->next;
	}
	return (0);
}

int	convert_dummy_quotes(t_line *origin, int *i, int *is_quote, int quote)
{
	while (origin->cmd_line[(*i)] && (*is_quote) == 0)
	{
		++(*i);
		if (ft_isspace(origin->cmd_line[(*i)]))
			origin->cmd_line[(*i)] = (char)DUMMY;
		else if (origin->cmd_line[(*i)] == quote)
			(*is_quote) = 1;
	}
	if ((*is_quote) == 0)
		return (1);
	return (0);
}
