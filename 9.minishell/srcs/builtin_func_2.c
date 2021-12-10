#include "minishell.h"

int	exec_builtin_cd(t_order *curr, char ***env)
{
	char	*pwd_str;
	char	*home_path;

	pwd_str = getcwd(0, 300);
	if (!curr->args)
	{
		home_path = get_env_value(g_state.local_envp, "HOME");
		if (home_path == NULL)
		{
			ft_putstr_fd("W.A.P-$HELL : cd: HOME not set\n", STD_ERR);
			return (exec_builtin_return(curr, EXIT_FAILURE));
		}
		curr->args = arr_new(home_path);
	}
	if (chdir(curr->args[0]) == -1)
	{
		ft_free_str(&pwd_str);
		print_errno(errno);
		return (exec_builtin_return(curr, EXIT_FAILURE));
	}
	return (exec_builtin_cd_2(curr, env, pwd_str));
}

int	exec_builtin_cd_2(t_order *curr, char ***env, char *pwd_str)
{
	int		old_pwd;
	int		pwd;

	old_pwd = get_env_key_address(*env, "OLDPWD");
	pwd = get_env_key_address(*env, "PWD");
	if (old_pwd)
	{
		ft_free_str(&(*env)[old_pwd]);
		(*env)[old_pwd] = ft_strjoin("OLDPWD=", pwd_str);
	}
	ft_free_str(&pwd_str);
	pwd_str = getcwd(0, 300);
	if (pwd)
	{
		ft_free_str(&(*env)[pwd]);
		(*env)[pwd] = ft_strjoin("PWD=", pwd_str);
	}
	ft_free_str(&pwd_str);
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}

int	exec_builtin_export(t_order *curr, char ***env)
{
	if (curr->args == FALSE)
	{
		print_arr(*env);
		return (exec_builtin_return(curr, EXIT_SUCCESS));
	}
	return (exec_builtin_export_2(curr, env));
}

int	exec_builtin_export_2(t_order *curr, char ***env)
{
	int		i;
	int		address;
	char	*key;

	i = 0;
	while (curr->args[i])
	{
		key = get_env_key(curr->args[i]);
		if (key == NULL)
			return (exec_builtin_return(curr, EXIT_FAILURE));
		address = get_env_key_address(*env, key);
		if (address)
		{
			ft_free_str(&(*env)[address]);
			(*env)[address] = ft_strdup(curr->args[i]);
		}
		else
		{
			ft_free_str(&key);
			*env = arr_add_str(*env, curr->args[i]);
		}
		i++;
	}
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}

int	exec_builtin_unset(t_order *curr, char ***env)
{
	int	i;

	if (curr->args == NULL)
		return (exec_builtin_return(curr, EXIT_SUCCESS));
	i = 0;
	while (curr->args[i])
	{
		if (is_unset_key_format(curr->args[i]) == \
TRUE && get_env_value(*env, curr->args[i]))
			*env = get_env_delete(*env, curr->args[i]);
		i++;
	}
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}
