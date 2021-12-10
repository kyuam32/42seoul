#include "minishell.h"

char	*env_to_str(char *env, int dummy, int is_dquote)
{
	char	*str;
	char	*swap;
	int		i;

	if (get_env_value(g_state.local_envp, env) == NULL)
		str = ft_strdup("");
	else
		str = ft_strdup(get_env_value(g_state.local_envp, env));
	if (dummy > 0 && is_dquote == 0)
	{
		swap = env_value_in_dquote(str);
		free(str);
		str = swap;
	}
	if (dummy > 0)
	{
		i = -1;
		while (str[++i])
		{
			if (ft_isspace(str[i]))
				str[i] = (char)DUMMY;
		}
	}
	return (str);
}

char	*env_value_in_dquote(char *str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = env_word_len_with_blank(str) + 1;
	res = ft_str_init(len);
	i = 0;
	j = 0;
	while (ft_isspace(str[j]))
		j++;
	while (i < len && str[j])
	{
		if (ft_isspace(str[j]) != 1)
			res[i++] = str[j++];
		else if (ft_isspace(str[j]))
		{
			res[i++] = str[j++];
			while (ft_isspace(str[j]))
				j++;
		}
	}
	res[i] = '\0';
	return (res);
}

int	env_word_len_with_blank(char *str)
{
	char	**tmp;
	int		blank_cnt;
	int		res_len;
	int		word_len;

	tmp = ft_split(str, ' ');
	word_len = 0;
	blank_cnt = -1;
	while (tmp[++blank_cnt])
		word_len += ft_strlen(tmp[blank_cnt]);
	res_len = word_len + blank_cnt;
	if (tmp != NULL)
		ft_free_arr(&tmp);
	return (res_len);
}
