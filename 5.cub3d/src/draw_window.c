/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:41:44 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 15:35:04 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*draw_texture_path(t_data *data, double *wall_x)
{
	if (data->draw.side == VIRTICAL_SIDE)
	{
		if (data->cam.dir.x < 0)
		{
			*wall_x = 64.0 - *wall_x;
			return (&data->texture.we);
		}
		else
			return (&data->texture.ea);
	}
	else
	{
		if (data->cam.dir.y < 0)
			return (&data->texture.no);
		else
		{
			*wall_x = 64.0 - *wall_x;
			return (&data->texture.so);
		}
	}
	return (0);
}

void	draw_texture(t_data *data, int x, int y, int height)
{
	t_img		*img;
	double		repeat;
	double		offset;
	double		wall_x;
	int			i;

	offset = 0;
	repeat = 1.0 * 64 / height;
	if (data->draw.dist_adj < 1)
	{
		offset = 64 * (1.0 - data->draw.dist_adj) / 2;
		repeat = 1.0 * 64 * data->draw.dist_adj / height;
	}
	i = -1;
	if (data->draw.side == VIRTICAL_SIDE)
		wall_x = ((data->player.axis.y + data->cam.dist * data->cam.dir.y) - \
			floor(data->player.axis.y + data->cam.dist * data->cam.dir.y)) * 64;
	else
		wall_x = ((data->player.axis.x + data->cam.dist * data->cam.dir.x) - \
			floor(data->player.axis.x + data->cam.dist * data->cam.dir.x)) * 64;
	img = draw_texture_path(data, &wall_x);
	while (++i < height)
		data->img.data[(int)(y + i) * data->img.size_l / 4 + x] = \
			img->data[(int)(repeat * i + offset) * img->size_l / 4 + \
																(int)wall_x];
}

void	draw_sprite(t_data *data, int x, int y, int height)
{
	t_img		*img;
	double		repeat;
	double		offset;
	double		wall_x;
	int			i;

	i = -1;
	offset = 0;
	repeat = 1.0 * 64 / height;
	if (data->sprite.sp_adj_dist < 1)
	{
		offset = 64 * (1 - data->sprite.sp_adj_dist) / 2;
		repeat = 1.0 * 64 * data->sprite.sp_adj_dist / height;
	}
	img = &data->texture.sp;
	wall_x = 64.0 * data->sprite.sp_rad;
	while (++i < height)
	{
		if (img->data[(int)(repeat * i + offset) * \
				img->size_l / 4 + (int)wall_x] != -16777216)
			data->img.data[(int)(y + i) * data->img.size_l / 4 + x] = \
					img->data[(int)(repeat * i + offset) * \
											img->size_l / 4 + (int)wall_x];
	}
}

int		draw_convert_height(t_data *data, double dist)
{
	if (dist < 1)
		return (data->resolution_height / 2);
	return (data->resolution_height / dist / 2);
}

void	draw_window(t_data *data)
{
	int i;
	int ray_w;
	int mid;
	int img_height;
	int sp_height;

	ray_w = data->cam.ray_width * data->cam.curr_precision;
	mid = data->resolution_height / 2;
	sp_height = draw_convert_height(data, data->sprite.sp_adj_dist);
	img_height = draw_convert_height(data, data->draw.dist_adj);
	i = -1;
	while (++i < data->cam.ray_width)
	{
		v_iput(&data->draw.start, i + ray_w, 0);
		v_iput(&data->draw.end, i + ray_w, mid - img_height);
		data->draw.color = data->texture.ceiling;
		draw_line(data);
		draw_texture(data, i + ray_w, mid - img_height, img_height * 2);
		v_iput(&data->draw.start, i + ray_w, mid + img_height);
		v_iput(&data->draw.end, i + ray_w, mid + mid);
		data->draw.color = data->texture.floor;
		draw_line(data);
		if (data->draw.tile == '2')
			draw_sprite(data, i + ray_w, mid - sp_height, sp_height * 2);
	}
}
