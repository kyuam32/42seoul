#include "minishell.h"

int	exception_handler(char *buf)
{
	if (exception_only_space(buf))
		return (-1);
	if (exception_unclosed_quotes(buf) || exception_invalid_redirection(buf))
	{
		ft_putstr_fd("syntax error\n", STD_ERR);
		return (-1);
	}
	return (0);
}

int	exception_invalid_redirection(char *buf)
{
	int		is_quote;
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (buf[i])
	{
		is_quote = 0;
		if (skip_quotes(buf, &i, &is_quote) == 1)
			return (1);
		if (buf[i] == '>' || buf[i] == '<')
		{
			cnt = i;
			while (buf[i] && (buf[i] == '>' || buf[i] == '<'))
				i++;
			if ((i - cnt) > 2)
				return (1);
			else
				i -= 1;
		}
		i++;
	}
	return (0);
}

int	exception_unclosed_quotes(char *buf)
{
	int		is_quote;
	int		i;

	i = 0;
	while (buf[i])
	{
		is_quote = 0;
		if (skip_quotes(buf, &i, &is_quote) == 1)
			return (1);
		if (buf[i] != '\0')
			i++;
	}
	return (0);
}

int	exception_only_space(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (ft_isspace(buf[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
