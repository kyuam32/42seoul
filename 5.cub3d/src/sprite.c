/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:42:41 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/10 18:33:13 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_hit(t_data *data, t_vector *hit, int x, int y)
{
	t_vector	*cur;

	cur = &data->player.axis;
	v_iput(hit, ((cur->x > x) ? x + 1 : x), ((cur->y > y) ? y + 1 : y));
	if (data->sprite.sp_side == VIRTICAL_SIDE)
		hit->y = (data->player.axis.y + \
				(data->sprite.sp_dist * data->cam.dir.y));
	else
		hit->x = (data->player.axis.x + \
				(data->sprite.sp_dist * data->cam.dir.x));
}

void	sprite_ray_rad(t_data *data, int x, int y)
{
	t_vector	*cur;
	t_vector	*hit;
	t_vector	rad;

	cur = &data->player.axis;
	hit = &data->sprite.hit;
	sprite_hit(data, hit, x, y);
	rad.x = (atan2((hit->y - cur->y), (hit->x - cur->x)));
	if ((cur->x <= x + 1 && cur->y <= y))
		rad.y = (atan2((y - cur->y), (x + 1 - cur->x)));
	else if ((cur->x > x + 1 && cur->y <= y + 1))
	{
		if (rad.x < 0)
			rad.x = PI + PI + rad.x;
		rad.y = (atan2((y + 1 - cur->y), (x + 1 - cur->x)));
	}
	else if ((cur->x >= x && cur->y >= y + 1))
		rad.y = (atan2((y + 1 - cur->y), (x - cur->x)));
	else if ((cur->x < x && cur->y > y))
		rad.y = (atan2((y - cur->y), (x - cur->x)));
	data->sprite.sp_rad = fabs(rad.x - rad.y) / data->sprite.sp_rad;
}

void	sprite_rad_inlines(t_data *data, t_vector *rad, int x, int y)
{
	t_vector	*cur;

	cur = &data->player.axis;
	if (x <= cur->x && cur->x <= x + 1)
	{
		if (cur->y > y)
			y += 1;
		rad->x = (PI - atan2(fabs(y - cur->y), fabs(x - cur->x)));
		rad->y = (atan2(fabs(y - cur->y), fabs(x + 1 - cur->x)));
	}
	else if (y <= cur->y && cur->y <= y + 1)
	{
		if (cur->x > x)
			x += 1;
		rad->x = (atan2(fabs(y - cur->y), fabs(x - cur->x)));
		rad->y = (atan2(fabs(y + 1 - cur->y), fabs(x - cur->x))) * -1;
	}
}

void	sprite_rad(t_data *data, int x, int y)
{
	t_vector	*cur;
	t_vector	rad;

	cur = &data->player.axis;
	if ((x <= cur->x && cur->x <= x + 1) || (y <= cur->y && cur->y <= y + 1))
		sprite_rad_inlines(data, &rad, x, y);
	else if ((cur->x < x && cur->y < y) || (cur->x > x && cur->y > y))
	{
		rad.x = (atan2((y + 1 - cur->y), (x - cur->x)));
		rad.y = (atan2((y - cur->y), (x + 1 - cur->x)));
	}
	else if ((cur->x > x && cur->y < y) || (cur->x < x && cur->y > y))
	{
		rad.x = (atan2((y - cur->y), (x - cur->x)));
		rad.y = (atan2((y + 1 - cur->y), (x + 1 - cur->x)));
	}
	data->sprite.sp_rad = fabs(rad.x - rad.y);
}
