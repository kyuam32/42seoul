#include "minishell.h"

char	*get_env_value(char **arr, char *key)
{
	int	key_len;
	int	i;
	int	j;

	i = 0;
	if (key == NULL)
		return (NULL);
	key_len = ft_strlen(key);
	while (arr[i] && key_len)
	{
		j = 0;
		while (arr[i][j] == key[j] && arr[i][j] && key[j])
			j++;
		if (arr[i][j] == '=')
			return (&arr[i][j] + 1);
		i++;
	}
	return (NULL);
}

char	*get_env_key(char *str)
{
	char	*ret;
	int		i;

	i = is_env_format(str);
	if (i == FALSE)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!(ret))
	{
		print_errno(errno);
		return (NULL);
	}
	memcpy(ret, str, i);
	ret[i] = 0;
	return (ret);
}

int	get_env_key_address(char **arr, char *key)
{
	int	key_len;
	int	i;
	int	j;

	i = 0;
	key_len = ft_strlen(key);
	while (arr[i] && key_len)
	{
		j = 0;
		while (arr[i][j] == key[j] && arr[i][j] && key[j])
			j++;
		if (arr[i][j] == '=')
			return (i);
		i++;
	}
	return (FALSE);
}

char	**get_env_delete(char **arr, char *key)
{
	char	**ret;
	int		i;
	int		j;

	if (arr_len(arr) < 1)
		return (arr);
	ret = (char **)malloc(sizeof(char *) * (arr_len(arr)));
	if (!(ret))
	{
		print_errno(errno);
		return (arr);
	}
	i = 0;
	j = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > ft_strlen(key) && \
arr[i][ft_strlen(key)] == '=' && ft_strncmp(arr[i], key, ft_strlen(key)) == 0)
			i++;
		else
			ret[j++] = ft_strdup(arr[i++]);
	}
	ret[j] = NULL;
	ft_free_arr(&arr);
	return (ret);
}
