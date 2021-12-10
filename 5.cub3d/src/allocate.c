/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:52:13 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 16:44:06 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_system(t_data *data)
{
	data->system.mlx = mlx_init();
	data->system.win = mlx_new_window(data->system.mlx, \
			data->resolution_width, data->resolution_height, "Namkyu's Cub3d");
	data->img.ptr = mlx_new_image(data->system.mlx, \
			data->resolution_width, data->resolution_height);
	data->img.data = (int *)mlx_get_data_addr(data->img.ptr, \
				&data->img.bpp, &data->img.size_l, &data->img.endian);
}

void	allocate_texture(t_data *data)
{
	t_texture	*t;
	int			w;
	int			h;

	w = 64;
	h = 64;
	t = &data->texture;
	t->ea.ptr = mlx_xpm_file_to_image(data->system.mlx, t->path[EA_P], &w, &h);
	t->ea.data = (int *)mlx_get_data_addr(t->ea.ptr, \
									&t->ea.bpp, &t->ea.size_l, &t->ea.endian);
	t->we.ptr = mlx_xpm_file_to_image(data->system.mlx, t->path[WE_P], &w, &h);
	t->we.data = (int *)mlx_get_data_addr(t->we.ptr, \
									&t->we.bpp, &t->we.size_l, &t->we.endian);
	t->so.ptr = mlx_xpm_file_to_image(data->system.mlx, t->path[SO_P], &w, &h);
	t->so.data = (int *)mlx_get_data_addr(t->so.ptr, \
									&t->so.bpp, &t->so.size_l, &t->so.endian);
	t->no.ptr = mlx_xpm_file_to_image(data->system.mlx, t->path[NO_P], &w, &h);
	t->no.data = (int *)mlx_get_data_addr(t->no.ptr, \
									&t->no.bpp, &t->no.size_l, &t->no.endian);
	t->sp.ptr = mlx_xpm_file_to_image(data->system.mlx, t->path[SP_P], &w, &h);
	t->sp.data = (int *)mlx_get_data_addr(t->sp.ptr, \
									&t->sp.bpp, &t->sp.size_l, &t->sp.endian);
}

void	allocate_player(t_data *data)
{
	int scale;
	int	i;

	scale = 5;
	data->map.w_scale = scale;
	data->map.h_scale = scale;
	data->map.h_offset = data->resolution_height / scale * (scale - 1);
	data->map.cub_width = data->resolution_width / scale / data->map.col;
	data->map.cub_height = data->resolution_height / scale / data->map.row;
	data->player.mov_speed = 0.4;
	data->player.rot_speed = ray_cal_deg2rad(10);
	if (data->graphic == 0)
		data->graphic = 1;
	i = -1;
	while (++i < 5)
		ft_free(data->texture.path[i]);
}
