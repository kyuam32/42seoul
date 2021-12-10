/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:25:32 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 14:58:04 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*valid_trim(t_data *data, char *str, int skip)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = skip;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i++;
	while (str[j] == ' ')
		j--;
	if (i > j)
		exit_process(data, CUB_DATA_CORRUPTED);
	if (!(ret = (char *)malloc(sizeof(char) * (j - i + 2))))
		exit_process(data, MEM_ALLOCATE_FAILED);
	k = 0;
	while (i <= j)
	{
		ret[k] = str[i];
		k++;
		i++;
	}
	ret[k] = 0;
	return (ret);
}

void	valid_display(t_data *data)
{
	int cur_dp_width;
	int cur_dp_height;

	mlx_get_screen_size(data->system.mlx, &cur_dp_width, &cur_dp_height);
	if (data->resolution_width > cur_dp_width)
		data->resolution_width = cur_dp_width;
	else if (data->resolution_width < 150)
		data->resolution_width = 150;
	if (data->resolution_height > cur_dp_height)
		data->resolution_height = cur_dp_height;
	else if (data->resolution_height < 100)
		data->resolution_height = 100;
	data->check[R_W] += 1;
	data->check[R_H] += 1;
}

int		valid_rgb(t_data *data, char *line, int *object, int bit)
{
	int i;
	int temp;

	i = 0;
	if (ft_isdigit(line[i]) != 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	if ((temp = ft_atoi(&line[i])) > 255 || temp < 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	*object += temp << bit;
	while (ft_isdigit(line[i]))
		i++;
	i += skip_space(&line[i]);
	return (i);
}

void	valid_map(char *line, t_data *data)
{
	if (line[0] == 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	if (ft_isdigit(line[0]) || line[0] == ' ')
		map_copy(line, data);
}

void	valid_playerdir(t_data *data, char c, int row, int col)
{
	if (data->player.locate == 0)
	{
		data->player.locate = c;
		if (c == 'E')
			v_iput(&data->player.dir, 1, 0);
		else if (c == 'W')
			v_iput(&data->player.dir, -1, 0);
		else if (c == 'S')
			v_iput(&data->player.dir, 0, 1);
		else if (c == 'N')
			v_iput(&data->player.dir, 0, -1);
		data->player.axis.x = col + 0.5;
		data->player.axis.y = row + 0.5;
	}
	else
		exit_process(data, MAP_DATA_CORRUPTED);
}
