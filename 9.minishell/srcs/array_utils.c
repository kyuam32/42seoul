#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**arr_add_str(char **arr, char *str)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (arr_len(arr) + 2));
	if (!(ret))
	{
		print_errno(errno);
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	ft_free_arr(&arr);
	return (ret);
}

char	**arr_dup(char **arr)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (arr_len(arr) + 1));
	if (!(ret))
	{
		print_errno(errno);
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**arr_new(char *cmd)
{
	char	**ret;
	char	*temp;

	temp = ft_strjoin(cmd, "\n");
	if (!(temp))
	{
		print_errno(errno);
		return (NULL);
	}
	ret = ft_split(temp, '\n');
	if (!(ret))
	{
		ft_free_str(&temp);
		print_errno(errno);
		return (NULL);
	}
	ft_free_str(&temp);
	return (ret);
}
