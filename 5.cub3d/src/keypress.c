/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:35:22 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/09 15:51:37 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_move(t_data *data, t_vector *dir, int inv, int keycode)
{
	t_player	*player;

	player = &data->player;
	if (keycode == KEY_W || keycode == KEY_S)
		v_dput(dir, player->dir.x * inv, player->dir.y * inv);
	else if (keycode == KEY_A || keycode == KEY_D)
		v_dput(dir, player->dir.y * -1 * inv, player->dir.x * inv);
	if (data->map.map_arr[(int)(player->axis.y)]\
			[(int)(player->axis.x + dir->x * player->mov_speed)] != '1')
		player->axis.x += dir->x * player->mov_speed;
	if (data->map.map_arr[(int)(player->axis.y + dir->y * player->mov_speed)]\
			[(int)(player->axis.x)] != '1')
		player->axis.y += dir->y * player->mov_speed;
}

void	key_rotate(t_data *data, t_vector *dir, int inv, int keycode)
{
	t_player	*player;

	player = &data->player;
	v_dput(dir, player->dir.x, player->dir.y);
	player->dir.x = dir->x * cos(player->rot_speed * inv) - \
					dir->y * sin(player->rot_speed * inv);
	player->dir.y = dir->x * sin(player->rot_speed * inv) + \
					dir->y * cos(player->rot_speed * inv);
}

int		key_press(int keycode, t_data *data)
{
	t_player	*player;
	t_vector	dir;
	int			inv;

	player = &data->player;
	inv = 1;
	if (keycode == KEY_S || keycode == KEY_A || keycode == KEY_LEFT)
		inv *= -1;
	if (keycode == KEY_W || keycode == KEY_S || \
		keycode == KEY_A || keycode == KEY_D)
		key_move(data, &dir, inv, keycode);
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		key_rotate(data, &dir, inv, keycode);
	else if (keycode == KEY_ESC)
		exit_process(data, 0);
	return (0);
}
