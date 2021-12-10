#include "minishell.h"

void	order_que_free(t_order_que *que)
{
	t_order	*curr;
	t_order	*temp;

	curr = que->head;
	while (curr)
	{
		ft_free_str(&curr->path);
		ft_free_arr(&curr->args);
		redir_que_free(&curr->redir_que);
		temp = curr;
		curr = curr->next;
		ft_memset(temp, 0, sizeof(t_order));
		free(temp);
	}
	ft_memset(que, 0, sizeof(t_order_que));
}

int	order_enque(t_order_que *que)
{
	t_order	*new;

	new = (t_order *)malloc(sizeof(t_order));
	if (!(new))
		print_errno(errno);
	ft_memset(new, 0, sizeof(t_order));
	if (que->tail == NULL)
	{
		new->next = NULL;
		que->head = new;
	}
	else
	{
		new->prev = que->tail;
		que->tail->next = new;
	}
	new->next = NULL;
	que->tail = new;
	que->size++;
	return (0);
}

void	order_args_parse(t_order *curr, char *cmd)
{
	if (curr->args == NULL)
		curr->args = arr_new(cmd);
	else
		curr->args = arr_add_str(curr->args, cmd);
}

void	order_parse(t_order *curr, char **split, char **env)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (i == 0 && !is_redir(split[i]))
		{
			curr->builtin = is_builtin(split[i]);
			if (curr->builtin == FALSE)
			{
				curr->path = is_executable(split[i], env);
				if (curr->path)
					order_args_parse(curr, split[i]);
			}
		}
		else if (is_redir(split[i]) == TRUE)
		{
			redir_parse(&curr->redir_que, split[i], split[i + 1]);
			i++;
		}
		else
			order_args_parse(curr, split[i]);
		i++;
	}
}

int	order_set(t_order_que *que_order, t_line_que *que_line, char **env)
{
	t_line	*curr_line;
	t_order	*curr_order;

	curr_line = que_line->head;
	while (curr_line)
	{
		if (is_empty_node(curr_line))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", STD_ERR);
			return (EXIT_FAILURE);
		}
		order_enque(que_order);
		curr_order = que_order->tail;
		order_parse(curr_order, curr_line->splited, env);
		curr_line = curr_line->next;
	}
	return (EXIT_SUCCESS);
}
