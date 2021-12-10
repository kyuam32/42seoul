/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:45 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 16:00:56 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ray_cal_deg2rad(int x)
{
	return (x * PI / 180);
}

void	ray_cal_delta(t_data *data, t_vector *delta, \
						t_vector *distance, t_vector *dir)
{
	t_vector	*axis;

	axis = &data->player.axis;
	if (dir->y == 0)
		delta->x = 0;
	else if (dir->x == 0)
		delta->x = 1;
	else
		delta->x = fabs(1 / dir->x);
	if (dir->x == 0)
		delta->y = 0;
	else if (dir->y == 0)
		delta->y = 1;
	else
		delta->y = fabs(1 / dir->y);
	if (dir->x > 0)
		distance->x = fabs(((int)axis->x + 1 - axis->x) * delta->x);
	else
		distance->x = fabs(((int)axis->x - axis->x) * delta->x);
	if (dir->y > 0)
		distance->y = fabs(((int)axis->y + 1 - axis->y) * delta->y);
	else
		distance->y = fabs(((int)axis->y - axis->y) * delta->y);
}

void	ray_cal_distance(t_data *data, t_vector *delta, \
						t_vector *distance, t_vector *dir)
{
	if (distance->x < distance->y)
	{
		distance->x += delta->x;
		data->draw.side = VIRTICAL_SIDE;
	}
	else
	{
		distance->y += delta->y;
		data->draw.side = HORIZOTAL_SIDE;
	}
	if (data->draw.side == VIRTICAL_SIDE)
		data->cam.dist = distance->x - delta->x;
	else
		data->cam.dist = distance->y - delta->y;
	data->draw.dist_adj = (data->player.dir.x * data->cam.dir.x + \
			data->player.dir.y * data->cam.dir.y) * data->cam.dist;
}
