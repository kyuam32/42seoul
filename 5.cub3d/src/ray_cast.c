/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:42:34 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 16:41:00 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ray_hit(t_data *data, int x_map, int y_map)
{
	if (data->map.map_arr[y_map][x_map] == '1')
	{
		draw_rectangle(data, x_map, y_map, 0x663300);
		return (1);
	}
	else if (data->map.map_arr[y_map][x_map] == '2')
	{
		data->draw.tile = '2';
		data->sprite.sp_side = data->draw.side;
		if (data->sprite.sp_dist == 0)
		{
			data->sprite.sp_dist = data->cam.dist;
			sprite_rad(data, x_map, y_map);
			sprite_ray_rad(data, x_map, y_map);
			data->sprite.sp_adj_dist = \
				hypot((y_map + 0.5 - data->player.axis.y), \
				(x_map + 0.5 - data->player.axis.x));
		}
		draw_rectangle(data, x_map, y_map, 0x666699);
		return (0);
	}
	return (0);
}

void	ray_distance(t_data *data, t_vector *dir)
{
	t_vector	delta;
	t_vector	distance;
	int			x_map;
	int			y_map;
	int			hit;

	hit = 0;
	x_map = (int)(data->player.axis.x);
	y_map = (int)(data->player.axis.y);
	data->draw.tile = 0;
	data->sprite.sp_dist = 0;
	ray_cal_delta(data, &delta, &distance, dir);
	while (hit == 0)
	{
		if (distance.x < distance.y)
			x_map += dir->x > 0 ? 1 : -1;
		else
			y_map += dir->y > 0 ? 1 : -1;
		ray_cal_distance(data, &delta, &distance, dir);
		hit = ray_hit(data, x_map, y_map);
	}
}

void	ray_cast(t_data *data, void (*draw_target)(t_data *))
{
	double		cur_dir;

	cur_dir = data->cam.fov / 2 * -1;
	data->cam.curr_precision = 0;
	while (cur_dir < data->cam.fov / 2)
	{
		data->cam.dir.x = data->player.dir.x * \
			cos(cur_dir) - data->player.dir.y * sin(cur_dir);
		data->cam.dir.y = data->player.dir.x * \
			sin(cur_dir) + data->player.dir.y * cos(cur_dir);
		ray_distance(data, &data->cam.dir);
		draw_target(data);
		data->cam.curr_precision++;
		cur_dir += data->cam.fov / data->cam.fov_precision;
	}
}

void	ray_initalize(t_data *data)
{
	data->cam.fov = ray_cal_deg2rad(60);
	data->cam.fov_precision = data->resolution_width / data->graphic;
	data->cam.ray_width = data->resolution_width / data->cam.fov_precision;
	ray_cast(data, draw_window);
	m_map_wall(data);
	ray_cast(data, draw_ray);
	m_map_grid(data);
	m_map_player(data);
}
