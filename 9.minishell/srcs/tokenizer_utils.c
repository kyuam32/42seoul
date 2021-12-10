#include "minishell.h"

int	ft_is_special_char(char c)
{
	if (c == ' ' || c == '\0' || c == '|' || c == '<' || c == '>' || \
		c == (char)DQUOTE || c == (char)SQUOTE || c == ';')
		return (1);
	return (0);
}

int	ft_is_redirection(char *cmd_line, int i)
{
	if (cmd_line[i] == '<')
	{
		if (cmd_line[i + 1])
			if (cmd_line[i + 1] == '<')
				return (2);
		return (1);
	}
	else if (cmd_line[i] == '>')
	{
		if (cmd_line[i + 1])
			if (cmd_line[i + 1] == '>')
				return (2);
		return (1);
	}
	return (0);
}

int	ft_original_redirection(char *splited)
{
	if (ft_strcmp(splited, "<") == 0)
		return (1);
	else if (ft_strcmp(splited, ">") == 0)
		return (1);
	else if (ft_strcmp(splited, "<<") == 0)
		return (1);
	else if (ft_strcmp(splited, ">>") == 0)
		return (1);
	return (0);
}

void	print_splited_line(t_line_que *line)
{
	t_line	*origin;
	int		node;
	int		i;

	while (line->head->prev != NULL)
		line->head = line->head->prev;
	origin = line->head;
	node = 0;
	while (origin)
	{
		if (origin->splited == NULL)
			return ;
		ft_putstr_fd("\x1b[33m""============================ node\n", 1);
		i = 0;
		while (origin->splited[i])
		{
			ft_putstr_fd("|", 1);
			ft_putstr_fd(origin->splited[i++], 1);
			ft_putstr_fd("|\n", 1);
		}
		ft_putstr_fd("============================ node\n\n""\x1b[0m", 1);
		origin = origin->next;
		node++;
	}
}

void	print_cmd_line(t_line_que *line)
{
	t_line	*origin;
	int		node;

	while (line->head->prev != NULL)
		line->head = line->head->prev;
	origin = line->head;
	node = 0;
	while (origin)
	{
		if (origin->cmd_line == NULL)
			return ;
		ft_putstr_fd("\x1b[33m""============================ node\n", 1);
		ft_putstr_fd("|", 1);
		ft_putstr_fd(origin->cmd_line, 1);
		ft_putstr_fd("|\n", 1);
		ft_putstr_fd("============================ node\n\n""\x1b[0m", 1);
		origin = origin->next;
		node++;
	}
}
