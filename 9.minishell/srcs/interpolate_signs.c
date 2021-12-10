/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_signs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: easternstar <easternstar@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:48:11 by easternstar       #+#    #+#             */
/*   Updated: 2021/07/24 16:53:42 by easternstar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpolate_redirection_blank(t_line_que *line)
{
	t_line	*origin;
	int		is_quote;
	int		i;

	origin = line->head;
	while (origin)
	{
		i = 0;
		while (origin->cmd_line[i])
		{
			is_quote = 0;
			if (skip_quotes(origin->cmd_line, &i, &is_quote) == 1)
				return (0);
			if (ft_is_redirection(origin->cmd_line, i) > 0)
				put_buffer(origin, &i);
			if (origin->cmd_line[i] == '\0')
				break ;
			i++;
		}
		origin = origin->next;
	}
	return (0);
}

int	interpolate_dollar_sign(t_line_que *line)
{
	t_line	*origin;
	int		is_squote;
	int		is_dquote;
	int		i;

	origin = line->head;
	while (origin)
	{
		i = 0;
		is_dquote = 0;
		while (origin->cmd_line[i])
		{
			is_squote = 0;
			if (is_dquote != 1)
				if (skip_squote(origin->cmd_line, &i, &is_squote) == 1)
					return (0);
			ft_is_dquote(origin->cmd_line[i], &is_dquote);
			if (origin->cmd_line[i] == '$')
				interpolate_dollar_sign_sub(origin, &i, &is_dquote);
			if (origin->cmd_line[i] != '\0')
				i++;
		}
		origin = origin->next;
	}
	return (0);
}

void	ft_is_dquote(char cmd_line, int *is_dquote)
{
	if (cmd_line == DQUOTE && (*is_dquote) == 0)
		(*is_dquote) = 1;
	else if (cmd_line == DQUOTE && (*is_dquote) == 1)
		(*is_dquote) = 0;
}

int	interpolate_dollar_sign_sub(t_line *origin, int *i, int *is_dquote)
{
	int		env_i;
	char	*inter;
	char	*env;

	env_i = ++(*i);
	while (origin->cmd_line[(*i)] && \
					ft_is_special_char(origin->cmd_line[(*i)]) == 0)
		(*i)++;
	if (env_i < (*i))
	{
		inter = ft_substr(origin->cmd_line, env_i, ((*i) - env_i));
		if (ft_strcmp(inter, "?") == 0)
			env = ft_itoa(g_state.exit_status);
		else
			env = env_to_str(inter, 1, (*is_dquote));
		free(inter);
		interpolate_env_var(origin, env, (env_i - 1));
		if (ft_strlen(env) == 0)
			(*i) = env_i - 1;
		else if (ft_strlen(env) > 0)
			(*i) = (env_i + ft_strlen(env)) - 1;
		free(env);
	}
	ft_is_dquote(origin->cmd_line[(*i)], is_dquote);
	return (0);
}
