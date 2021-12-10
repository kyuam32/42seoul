#include "minishell.h"

int	interpolate_tilde_sign(t_line_que *line)
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
			{
				if (j == 0 && origin->splited[i][j] == '~')
				{
					j += 1;
					if (origin->splited[i][j] == '\0' || \
												origin->splited[i][j] == '/')
						convert_tilde_to_home(origin, i, j);
				}
			}
		}
		origin = origin->next;
	}
	return (0);
}

int	convert_tilde_to_home(t_line *origin, int i, int j)
{
	char	*env;
	char	*env_bs;
	char	*bs_res;

	env = env_to_str("HOME", 0, 0);
	if (origin->splited[i][j] == '\0')
	{		
		free(origin->splited[i]);
		origin->splited[i] = env;
	}
	else if (origin->splited[i][j] == '/')
	{
		env_bs = ft_substr(origin->splited[i], j, \
									(ft_strlen(origin->splited[i]) - j));
		bs_res = ft_strjoin(env, env_bs);
		free(origin->splited[i]);
		origin->splited[i] = bs_res;
		free(env_bs);
		free(env);
	}
	return (0);
}
