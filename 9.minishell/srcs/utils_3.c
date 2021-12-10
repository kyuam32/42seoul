#include "minishell.h"

int	is_env_init_char(char *str, char *function_name)
{
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
	{
		ft_putstr_fd(function_name, STD_OUT);
		ft_putstr_fd(": '", STD_OUT);
		ft_putstr_fd(str, STD_OUT);
		ft_putstr_fd("' : not a valid identifier\n", STD_OUT);
		return (FALSE);
	}
	return (TRUE);
}

int	is_env_format(char *str)
{
	int	i;

	i = 0;
	if (is_env_init_char(str, "export") == FALSE)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	ft_putstr_fd("export: '", STD_OUT);
	ft_putstr_fd(str, STD_OUT);
	ft_putstr_fd("' : not a valid identifier\n", STD_OUT);
	return (FALSE);
}

int	is_unset_key_format(char *str)
{
	int	i;

	i = 0;
	if (is_env_init_char(str, "unset") == FALSE)
		return (FALSE);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("unset: '", STD_OUT);
			ft_putstr_fd(str, STD_OUT);
			ft_putstr_fd("' : not a valid identifier\n", STD_OUT);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	print_errno(int err)
{
	int	pid;
	int	status;

	if (g_state.is_child == TRUE)
	{
		dup2(STD_ERR, STD_OUT);
		printf("W.A.P.$HELL: %s\n", strerror(err));
		exit(1);
	}
	else
	{
		pid = fork();
		if (pid == CHILD)
		{
			dup2(STD_ERR, STD_OUT);
			printf("W.A.P.$HELL: %s\n", strerror(err));
			exit(1);
		}
	}
	wait(&status);
	return (g_state.exit_status = 1);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], STD_OUT);
		ft_putstr_fd("\n", STD_OUT);
		i++;
	}
}
