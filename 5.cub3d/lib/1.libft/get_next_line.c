/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:06:30 by nlee              #+#    #+#             */
/*   Updated: 2021/02/15 14:52:17 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	str_process(char **storage, char **line, int flag)
{
	char		*temp;
	int			len;

	len = ft_strlen(*storage);
	(*storage)[flag] = '\0';
	*line = ft_strdup(*storage);
	if (len == (flag + 1))
	{
		free(*storage);
		*storage = 0;
		return (1);
	}
	temp = ft_strdup(*storage + flag + 1);
	free(*storage);
	*storage = temp;
	return (1);
}

int	end_process(char **storage, char **line)
{
	if (*storage)
	{
		*line = *storage;
		*storage = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*storage[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	int			read_len;
	int			flag;

	if (fd < 0 || fd > OPEN_MAX || !(line) || BUFFER_SIZE < 1)
		return (-1);
	while ((read_len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_len] = '\0';
		temp = ft_strjoin(storage[fd], buff);
		free(storage[fd]);
		storage[fd] = temp;
		if ((flag = check_newline(storage[fd])) >= 0)
			return (str_process((&storage[fd]), line, flag));
	}
	if (read_len <= -1)
		return (-1);
	if (storage[fd] && (flag = check_newline(storage[fd])) >= 0)
		return (str_process((&storage[fd]), line, flag));
	return (end_process(&storage[fd], line));
}
