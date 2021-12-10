/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:22:46 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 14:58:44 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_allocate(t_data *data)
{
	t_minimap	*map;
	int			i;
	int			j;

	i = 0;
	map = &data->map;
	if (!(map->map_arr = (char **)malloc(sizeof(char *) * map->row + 1)))
		exit_process(data, MEM_ALLOCATE_FAILED);
	while (i < map->row)
	{
		if (!(map->map_arr[i] = (char *)malloc(sizeof(char) * map->col + 1)))
			exit_process(data, MEM_ALLOCATE_FAILED);
		j = 0;
		while (j < map->col)
		{
			map->map_arr[i][j] = '1';
			j++;
		}
		map->map_arr[i][map->col] = 0;
		i++;
	}
	map->map_arr[i] = NULL;
}

void	map_str_to_array(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = data->map.map_str;
	while (*str)
	{
		if (*str == '.')
		{
			j = 0;
			i++;
		}
		else
		{
			if (ft_strchr("EWSN", *str))
				valid_playerdir(data, *str, i, j);
			else if (!(ft_strchr("012 ", *str)))
				exit_process(data, MAP_DATA_CORRUPTED);
			data->map.map_arr[i][j] = *str;
			j++;
		}
		str++;
	}
}

void	map_sizecheck(t_data *data)
{
	int i;
	int row;
	int col;

	i = 0;
	col = 0;
	row = 0;
	while (data->map.map_str[i])
	{
		if (data->map.map_str[i] == '.')
		{
			row++;
			data->map.col = (data->map.col < col) ? col : data->map.col;
			col = 0;
		}
		else if (ft_strchr("012 EWSN", data->map.map_str[i]))
			col++;
		else
			exit_process(data, MAP_DATA_CORRUPTED);
		i++;
	}
	data->map.row = row;
	if (data->map.col < 3 || data->map.row < 3)
		exit_process(data, MAP_DATA_CORRUPTED);
}

void	map_create(t_data *data)
{
	int i;

	i = -1;
	while (++i < 10)
	{
		if (data->check[i] != 1)
			exit_process(data, CUB_DATA_CORRUPTED);
	}
	map_sizecheck(data);
	map_allocate(data);
	map_str_to_array(data);
	print_ptr(data->map.map_arr);
	map_dfs(data);
	ft_free(data->map.map_str);
}

void	map_copy(char *line, t_data *data)
{
	char *map;
	char *temp;

	if (ft_strchr(line, '.'))
	{
		printf("%s\n", line);
		exit_process(data, MAP_DATA_CORRUPTED);
	}
	if (!(map = ft_strjoin(data->map.map_str, line)))
		exit_process(data, MEM_ALLOCATE_FAILED);
	ft_free(data->map.map_str);
	temp = ft_strdup(map);
	ft_free(map);
	if (!(map = ft_strjoin(temp, ".")))
		exit_process(data, MEM_ALLOCATE_FAILED);
	ft_free(temp);
	data->map.map_str = map;
}
