#include "minishell.h"

int	order_print_unexecutable(t_order *curr_order, char *str)
{
	if ((curr_order->path == FALSE && \
			curr_order->builtin == FALSE && \
			!g_state.exit_status && !is_redir(str)))
	{
		g_state.exit_status = 127;
		ft_putstr_fd("W.A.P.$HELL: ", STD_OUT);
		ft_putstr_fd(str, STD_OUT);
		ft_putstr_fd(" : command not found\n", STD_OUT);
		return (TRUE);
	}
	return (FALSE);
}

int	order_print_directory(t_order *curr_order, char *str)
{
	struct stat		status;

	if (stat(curr_order->path, &status) == \
			0 && (status.st_mode & S_IFDIR) && \
			!g_state.exit_status && !is_redir(str))
	{
		g_state.exit_status = 126;
		ft_putstr_fd("W.A.P.$HELL: ", STD_OUT);
		ft_putstr_fd(str, STD_OUT);
		ft_putstr_fd(" : is a directory\n", STD_OUT);
		return (TRUE);
	}
	return (FALSE);
}

int	is_orders_fine(t_order_que *order_que, t_line_que *line_que)
{
	t_order	*curr_order;
	t_line	*curr_line;

	curr_order = order_que->head;
	curr_line = line_que->head;
	if (!curr_order || !curr_line)
		return (FALSE);
	while (curr_order && curr_line)
	{
		if (order_print_directory(curr_order, curr_line->splited[0]))
			return (FALSE);
		if (order_print_unexecutable(curr_order, curr_line->splited[0]))
			return (FALSE);
		curr_order = curr_order->next;
		curr_line = curr_line->next;
	}
	return (TRUE);
}
