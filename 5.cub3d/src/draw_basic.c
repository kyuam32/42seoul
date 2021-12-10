/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:35:31 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 15:53:59 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_data *data)
{
	t_vector	*axis;
	t_vector	*cam;
	int			width;
	int			height;

	axis = &data->player.axis;
	cam = &data->cam.dir;
	width = data->map.cub_width;
	height = data->map.cub_height;
	v_iput(&data->draw.start, \
			axis->x * width, \
			axis->y * height + data->map.h_offset);
	v_iput(&data->draw.end, \
			(axis->x + data->cam.dist * cam->x) * width, \
			(axis->y + data->cam.dist * cam->y) * height + data->map.h_offset);
	data->draw.color = 0xFFFF99;
	draw_line(data);
}

void	draw_rectangle(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;

	x *= data->map.cub_width;
	y = y * data->map.cub_height + data->map.h_offset;
	i = 0;
	while (i < data->map.cub_height)
	{
		j = 0;
		while (j < data->map.cub_width)
		{
			data->img.data[(y + i) * (data->img.size_l / 4) + (j + x)] = color;
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *data)
{
	t_vector	start;
	t_vector	end;
	t_vector	delta;
	double		step;

	start.x = data->draw.start.x;
	start.y = data->draw.start.y;
	end.x = data->draw.end.x;
	end.y = data->draw.end.y;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	step = (fabs(delta.x) > fabs(delta.y)) ? fabs(delta.x) : fabs(delta.y);
	delta.x /= step;
	delta.y /= step;
	while (fabs(end.x - start.x) >= 1 || fabs(end.y - start.y) >= 1)
	{
		data->img.data[(int)floor(start.y) * \
			(data->img.size_l / 4) + (int)floor(start.x)] = data->draw.color;
		start.x += delta.x;
		start.y += delta.y;
	}
}
