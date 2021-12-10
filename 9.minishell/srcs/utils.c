#include "minishell.h"

char	*string_to_lower(char *string)
{
	int		i;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!(ret))
	{
		print_errno(errno);
		return (NULL);
	}
	i = 0;
	while (string[i])
	{
		ret[i] = (char)ft_tolower(string[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	ft_free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_arr(char ***arr)
{
	int	i;

	if (*arr)
	{
		i = 0;
		while ((*arr)[i])
		{
			ft_free_str(&(*arr)[i]);
			i++;
		}
		ft_free_str(&(*arr)[i]);
		free(*arr);
		*arr = NULL;
	}
}

int	is_there_child(t_order_que *que)
{
	t_order	*curr;

	curr = que->head;
	while (curr)
	{
		if (curr->stream.pid)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

char	is_builtin(char *cmd)
{
	char	*string;
	char	ret;

	ret = FALSE;
	string = string_to_lower(cmd);
	if (!(ft_strcmp(string, "echo")))
		ret = B_ECHO;
	else if (!(ft_strcmp(string, "cd")))
		ret = B_CD;
	else if (!(ft_strcmp(string, "pwd")))
		ret = B_PWD;
	else if (!(ft_strcmp(string, "export")))
		ret = B_EXPORT;
	else if (!(ft_strcmp(string, "unset")))
		ret = B_UNSET;
	else if (!(ft_strcmp(string, "env")))
		ret = B_ENV;
	else if (!(ft_strcmp(string, "exit")))
		ret = B_EXIT;
	ft_free_str(&string);
	return (ret);
}
