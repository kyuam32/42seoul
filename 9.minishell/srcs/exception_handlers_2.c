#include "minishell.h"

int	ft_error_exit_syntax(char *inter)
{
	char	*prefix;
	char	*message;

	message = NULL;
	prefix = ft_strdup("syntax error near unexpected token `");
	if (ft_quoted_redirection(inter, 0) == 1)
		message = ft_strjoin(prefix, "<'\n");
	else if (ft_quoted_redirection(inter, 0) == 2)
		message = ft_strjoin(prefix, ">'\n");
	else if (ft_quoted_redirection(inter, 0) == 3)
		message = ft_strjoin(prefix, "<<'\n");
	else if (ft_quoted_redirection(inter, 0) == 4)
		message = ft_strjoin(prefix, ">>'\n");
	else if (ft_quoted_redirection(inter, 1) == 5)
		message = ft_strjoin(prefix, "<>'\n");
	else if (ft_quoted_redirection(inter, 1) == 6)
		message = ft_strjoin(prefix, ">'\n");
	else if (ft_strcmp(inter, "newline") == 0)
		message = ft_strjoin(prefix, "newline'\n");
	else if (ft_strcmp(inter, "|") == 0)
		message = ft_strjoin(prefix, "|'\n");
	ft_putstr_fd(message, STD_ERR);
	free(message);
	free(prefix);
	return (1);
}

int	ft_quoted_redirection(char *splited, int suspicious)
{
	if (ft_strcmp(splited, "'<") == 0)
		return (1);
	else if (ft_strcmp(splited, "'>") == 0)
		return (2);
	else if (ft_strcmp(splited, "'<<") == 0)
		return (3);
	else if (ft_strcmp(splited, "'>>") == 0)
		return (4);
	if (suspicious == 1)
	{
		if (ft_strcmp(splited, "<>") == 0)
			return (5);
		if (ft_strcmp(splited, "><") == 0)
			return (6);
	}
	return (0);
}

int	exception_redir_with_no_path(t_line_que *line)
{
	t_line	*origin;
	int		i;

	origin = line->head;
	while (origin)
	{
		i = 0;
		while (origin->splited[i])
		{
			if (ft_quoted_redirection(origin->splited[i], 0) > 0)
			{
				if (!origin->splited[i + 1] && origin->next)
					return (ft_error_exit_syntax("|"));
				else if (!origin->splited[i + 1] && !origin->next)
					return (ft_error_exit_syntax("newline"));
				else if (ft_quoted_redirection(origin->splited[i + 1], 1) > 0)
					return (ft_error_exit_syntax(origin->splited[i + 1]));
			}
			i++;
		}
		origin = origin->next;
	}
	return (0);
}
