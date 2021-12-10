/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:38:54 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/10 12:55:20 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	m_map_grid(t_data *data)
{
	t_minimap	*map;
	int			i;

	i = 0;
	map = &(data->map);
	while (i <= map->col)
	{
		v_iput(&(data->draw.start), i * map->cub_width, map->h_offset);
		v_iput(&(data->draw.end), i * map->cub_width, \
				map->h_offset + map->row * map->cub_height);
		data->draw.color = 0x000000;
		draw_line(data);
		i++;
	}
	i = 0;
	while (i < map->row)
	{
		v_iput(&(data->draw.start), 0, map->h_offset + i * map->cub_height);
		v_iput(&(data->draw.end), map->col * map->cub_width, \
				map->h_offset + i * map->cub_height);
		data->draw.color = 0x000000;
		draw_line(data);
		i++;
	}
}

void	m_map_wall(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map.row)
	{
		j = 0;
		while (j < data->map.col)
		{
			if (data->map.map_arr[i][j] == '0')
				draw_rectangle(data, j, i, 0x555555);
			else if (data->map.map_arr[i][j] == '1')
				draw_rectangle(data, j, i, 0x111111);
			else if (data->map.map_arr[i][j] == '2')
				draw_rectangle(data, j, i, 0x666699);
			else if (ft_memchr("EWSN", data->map.map_arr[i][j], 4))
				draw_rectangle(data, j, i, 0xFF0000);
			else
				draw_rectangle(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	m_map_player(t_data *data)
{
	int x;
	int y;

	x = data->player.axis.x * data->map.cub_width;
	y = data->player.axis.y * data->map.cub_height + data->map.h_offset;
	data->img.data[(y - 1) * data->img.size_l / 4 + x] = 0xFF0000;
	data->img.data[(y + 1) * data->img.size_l / 4 + x] = 0xFF0000;
	data->img.data[y * data->img.size_l / 4 + x] = 0xFF0000;
	data->img.data[y * data->img.size_l / 4 + x + 1] = 0xFF0000;
	data->img.data[y * data->img.size_l / 4 + x - 1] = 0xFF0000;
}
