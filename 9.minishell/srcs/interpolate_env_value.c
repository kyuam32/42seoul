#include "minishell.h"

int	interpolate_env_var(t_line *origin, char *env, int origin_i)
{
	char	*res;

	res = ft_str_init_env(origin, env);
	interpolate_env_var_sub(origin, res, env, origin_i);
	free(origin->cmd_line);
	origin->cmd_line = res;
	return (0);
}

void	interpolate_env_var_sub(t_line *origin, char *res, char *env, int ori)
{
	int		i;
	int		once;
	int		env_idx;
	int		res_idx;

	res_idx = 0;
	once = 0;
	i = 0;
	while (origin->cmd_line[i])
	{
		if (origin->cmd_line[i] == '$' && once == 0 && ori == i)
		{
			env_idx = -1;
			if (ft_strlen(env) > 0)
				while (env[++env_idx])
					res[res_idx++] = env[env_idx];
			while (origin->cmd_line[i] && \
						ft_is_special_char(origin->cmd_line[i]) == 0)
				i++;
			once = 1;
		}
		else
			res[res_idx++] = origin->cmd_line[i++];
	}
	res[res_idx] = '\0';
}

char	*ft_str_init_env(t_line *origin, char *env)
{
	char	*res;
	int		res_len;

	res_len = ft_strlen(env) + ft_strlen(origin->cmd_line) + 1;
	res = (char *)malloc(sizeof(char) * res_len);
	if (res == NULL)
		return (0);
	ft_bzero(res, res_len);
	return (res);
}

char	*ft_str_init(int res_len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (res_len));
	if (res == NULL)
		return (0);
	ft_bzero(res, res_len);
	return (res);
}
