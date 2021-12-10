/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:20:07 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 14:11:52 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_search_escape(t_data *data, char **is_visited, int x, int y)
{
	int i;
	int j;
	int a;
	int b;

	if (x == 0 || y == 0 || x == data->map.col - 1 || \
		y == data->map.row - 1 || data->map.map_arr[y][x] == ' ')
		exit_process(data, MAP_DATA_CORRUPTED);
	is_visited[y][x] = '1';
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			a = x + i;
			b = y + j;
			if (is_visited[b][a] != '1' && data->map.map_arr[b][a] != '1')
				map_search_escape(data, is_visited, a, b);
			j++;
		}
		i++;
	}
	return (0);
}

void	map_dfs_free(t_data *data)
{
	int i;

	i = 0;
	if (data->map.dfs != NULL)
	{
		while (i < data->map.row)
		{
			ft_free(data->map.dfs[i]);
			i++;
		}
		ft_free(data->map.dfs);
	}
}

void	map_dfs(t_data *data)
{
	int i;
	int j;

	i = 0;
	if (!(data->map.dfs = (char **)malloc(sizeof(char *) * data->map.row + 1)))
		exit_process(data, MEM_ALLOCATE_FAILED);
	while (i < data->map.row)
	{
		j = 0;
		if (!(data->map.dfs[i] = \
				(char *)malloc(sizeof(char) * data->map.col + 1)))
			exit_process(data, MEM_ALLOCATE_FAILED);
		data->map.dfs[i][data->map.col] = 0;
		while (j < data->map.col)
		{
			data->map.dfs[i][j] = '0';
			j++;
		}
		i++;
	}
	data->map.dfs[i] = NULL;
	map_search_escape(data, data->map.dfs, \
		(int)data->player.axis.x, (int)data->player.axis.y);
	map_dfs_free(data);
}
