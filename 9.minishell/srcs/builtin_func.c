#include "minishell.h"

int	exec_builtin_return(t_order *curr, int ret)
{
	if (curr->stream.pid == CHILD)
		exit (ret);
	return (ret);
}

void	exec_builtin(t_order *curr, char ***env)
{
	if (curr->builtin == B_ECHO)
		g_state.exit_status = exec_builtin_echo(curr);
	else if (curr->builtin == B_PWD)
		g_state.exit_status = exec_builtin_pwd(curr);
	else if (curr->builtin == B_ENV)
		g_state.exit_status = exec_builtin_env(curr, *env);
	else if (curr->builtin == B_CD)
		g_state.exit_status = exec_builtin_cd(curr, env);
	else if (curr->builtin == B_EXPORT)
		g_state.exit_status = exec_builtin_export(curr, env);
	else if (curr->builtin == B_UNSET)
		g_state.exit_status = exec_builtin_unset(curr, env);
	else if (curr->builtin == B_EXIT)
		exit(0);
	else
		exit(1);
}

int	exec_builtin_echo(t_order *curr)
{
	int	i;
	int	opt_flag;

	i = 0;
	opt_flag = FALSE;
	if (curr->args)
	{
		if (!(ft_strcmp(curr->args[i], "-n")))
		{
			opt_flag = TRUE;
			i++;
		}
		while (curr->args[i])
		{
			ft_putstr_fd(curr->args[i++], STD_OUT);
			if (curr->args[i])
				ft_putstr_fd(" ", STD_OUT);
		}
	}
	if (opt_flag == FALSE)
		ft_putstr_fd("\n", STD_OUT);
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}

int	exec_builtin_pwd(t_order *curr)
{
	char	*str;

	str = getcwd(0, 300);
	if (str == NULL)
	{
		print_errno(errno);
		return (exec_builtin_return(curr, EXIT_FAILURE));
	}
	ft_putstr_fd(str, STD_OUT);
	ft_putstr_fd("\n", STD_OUT);
	ft_free_str(&str);
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}

int	exec_builtin_env(t_order *curr, char **env)
{
	if (curr->args)
	{
		ft_putstr_fd("W.A.P-$HELL doesn't support env arguments!\n", STD_OUT);
		return (exec_builtin_return(curr, EXIT_FAILURE));
	}
	print_arr(env);
	return (exec_builtin_return(curr, EXIT_SUCCESS));
}
