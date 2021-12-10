#include "minishell.h"

int	skip_quotes(char *buf, int *i, int *is_quote)
{
	if (buf[(*i)] == DQUOTE)
	{
		*is_quote = 1;
		while (buf[(*i)] && *is_quote == 1)
		{
			++(*i);
			if (buf[(*i)] == DQUOTE)
				*is_quote = 0;
		}
		if (*is_quote == 1)
			return (1);
	}
	else if (buf[(*i)] == SQUOTE)
	{
		*is_quote = 1;
		while (buf[(*i)] && *is_quote == 1)
		{
			++(*i);
			if (buf[(*i)] == SQUOTE)
				*is_quote = 0;
		}
		if (*is_quote == 1)
			return (1);
	}
	return (0);
}

int	skip_squote(char *buf, int *i, int *is_quote)
{
	if (buf[(*i)] == SQUOTE)
	{
		*is_quote = 1;
		while (buf[(*i)] && *is_quote == 1)
		{
			++(*i);
			if (buf[(*i)] == SQUOTE)
				*is_quote = 0;
		}
		if (*is_quote == 1)
			return (1);
	}
	return (0);
}

int	trim_quotes(t_line *origin, int i, int *j, char quote)
{
	char	*res;
	int		res_idx;
	int		res_j;
	int		tmp_j;
	int		flag;

	res = ft_str_init(ft_strlen(origin->splited[i]) - 2 + 1);
	init_trim_func_args(&res_idx, &res_j, &tmp_j, &flag);
	while (res_idx < (int)(ft_strlen(origin->splited[i]) - 2 + 1) \
								&& origin->splited[i][res_j])
	{
		while (res_idx < (*j))
			res[res_idx++] = origin->splited[i][res_j++];
		if (origin->splited[i][res_j] == quote && flag < 2)
			trim_quotes_sub(&flag, &tmp_j, &res_j);
		if (origin->splited[i][res_j] == quote && flag == 1)
			trim_quotes_sub(&flag, &tmp_j, &res_j);
		if (origin->splited[i][res_j] != '\0')
			res[res_idx++] = origin->splited[i][res_j++];
	}
	res[res_idx] = '\0';
	free(origin->splited[i]);
	origin->splited[i] = res;
	return (tmp_j);
}

void	trim_quotes_sub(int *flag, int *tmp_j, int *res_j)
{
	(*flag) += 1;
	if ((*flag) == 2)
		(*tmp_j) = ((*res_j) - 2);
	(*res_j) += 1;
}

void	init_trim_func_args(int *res_idx, int *res_j, int *tmp_j, int *flag)
{
	(*res_idx) = 0;
	(*res_j) = 0;
	(*tmp_j) = 0;
	(*flag) = 0;
}
