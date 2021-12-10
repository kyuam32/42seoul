/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:50:31 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 14:10:49 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bitmap_header(t_bmheader *header, t_data *data)
{
	int			size;

	size = 4 * data->resolution_width * data->resolution_height;
	header->type1 = 'B';
	header->type2 = 'M';
	header->fsize = 54 + size;
	header->reserved1 = 0;
	header->reserved2 = 0;
	header->offbits = 54;
	header->isize = 40;
	header->width = data->resolution_width;
	header->height = -data->resolution_height;
	header->planes = 1;
	header->bitcount = 32;
	header->compression = 0;
	header->sizeimage = size;
	header->xpelspereter = data->resolution_width;
	header->ypelspereter = data->resolution_height;
	header->clrused = 0xffffff;
	header->clrimportant = 0;
}

void	bitmap_create(t_data *data)
{
	t_bmheader	header;
	int			fd;
	int			i;
	int			j;

	if ((fd = open("screenshot.bmp", O_RDWR | O_TRUNC | O_CREAT, 0666)) < 0)
		exit_process(data, CANT_OPEN_FILE);
	bitmap_header(&header, data);
	write(fd, &header, 54);
	i = -1;
	while (++i <= data->resolution_height)
	{
		j = -1;
		while (++j < data->resolution_width)
			write(fd, &data->img.data[i * data->img.size_l / 4 + j], 4);
	}
	close(fd);
}
