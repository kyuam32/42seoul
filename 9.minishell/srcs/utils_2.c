#include "minishell.h"

char	*is_executable(char *cmd, char **env)
{
	struct stat		status;
	char			**path_token;
	char			*cmd_str;
	char			*temp;

	cmd_str = string_to_lower(cmd);
	if (stat(cmd_str, &status) == 0 && \
		status.st_mode & S_IXUSR && !(status.st_mode & S_IFDIR))
		return (cmd_str);
	path_token = ft_split(get_env_value(env, "PATH"), ':');
	if (path_token == NULL)
		return (NULL);
	temp = cmd_str;
	cmd_str = ft_strjoin("/", temp);
	ft_free_str(&temp);
	return (is_executable_2(path_token, cmd_str));
}

char	*is_executable_2(char **path_token, char *cmd_str)
{
	struct stat		status;
	int				i;
	char			*temp;

	i = 0;
	while (path_token[i])
	{
		temp = ft_strjoin(path_token[i], cmd_str);
		if (stat(temp, &status) == 0 && \
			status.st_mode & S_IXUSR && !(status.st_mode & S_IFDIR))
		{
			ft_free_str(&cmd_str);
			ft_free_arr(&path_token);
			return (temp);
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_str(&cmd_str);
	ft_free_arr(&path_token);
	return (NULL);
}

int	is_empty_node(t_line *line)
{
	if (!(line))
		return (TRUE);
	if (line->cmd_line == NULL || line->cmd_line[0] == '\0')
		return (TRUE);
	if (line->splited == NULL || line->splited[0] == NULL || \
line->splited[0][0] == '\0')
		return (TRUE);
	return (FALSE);
}

int	is_redir(char *str)
{
	if (!(ft_strcmp(str, "'>")))
		return (TRUE);
	else if (!(ft_strcmp(str, "'<")))
		return (TRUE);
	else if (!(ft_strcmp(str, "'>>")))
		return (TRUE);
	else if (!(ft_strcmp(str, "'<<")))
		return (TRUE);
	return (FALSE);
}
