/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:09:09 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 15:34:26 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_rgb(char *str, int type, t_data *data, int *object)
{
	char	*line;
	int		i;
	int		bit;

	if (data->check[MAP_CHECK] == 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	line = valid_trim(data, str, 1);
	i = 0;
	i += valid_rgb(data, &line[i], object, 16);
	if (line[i] != ',')
		exit_process(data, CUB_DATA_CORRUPTED);
	i++;
	i += skip_space(&line[i]);
	i += valid_rgb(data, &line[i], object, 8);
	if (line[i] != ',')
		exit_process(data, CUB_DATA_CORRUPTED);
	i++;
	i += skip_space(&line[i]);
	i += valid_rgb(data, &line[i], object, 0);
	if (line[i] != 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	if (line[i] != 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	data->check[type] += 1;
	ft_free(line);
}

void	parse_resolution(char *str, t_data *data)
{
	char	*line;
	int		i;

	if (data->check[MAP_CHECK] == 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	line = valid_trim(data, str, 1);
	i = 0;
	if (ft_isdigit(line[i]) != 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	if ((data->resolution_width = ft_atoi(&line[i])) < 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	while (ft_isdigit(line[i]))
		i++;
	i += skip_space(&line[i]);
	if (ft_isdigit(line[i]) != 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	if ((data->resolution_height = ft_atoi(&line[i])) < 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	ft_free(line);
	valid_display(data);
}

void	parse_texture_path(char *str, int type, t_data *data)
{
	char	*line;
	int		i;
	int		fd;

	if (data->check[MAP_CHECK] == 1)
		exit_process(data, CUB_DATA_CORRUPTED);
	line = valid_trim(data, str, 2);
	i = ft_strlen(line);
	if (ft_memcmp((&line[i - 4]), ".xpm", 4) != 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	if (!(data->texture.path[type] = ft_strdup(line)))
		exit_process(data, MEM_ALLOCATE_FAILED);
	if ((fd = open(data->texture.path[type], O_RDONLY)) < 0)
		exit_process(data, CUB_DATA_CORRUPTED);
	ft_free(line);
	close(fd);
	data->check[type] += 1;
}

void	parse_info(char *line, t_data *data)
{
	if (line[0] == 'R' && line[1] == ' ')
		parse_resolution(line, data);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_texture_path(line, EA_P, data);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_texture_path(line, WE_P, data);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_texture_path(line, SO_P, data);
	else if (line[0] == 'N' && line[1] == 'O')
		parse_texture_path(line, NO_P, data);
	else if (line[0] == 'S' && line[1] == ' ')
		parse_texture_path(line, SP_P, data);
	else if (line[0] == 'F' && line[1] == ' ')
		parse_rgb(line, C_F, data, &data->texture.floor);
	else if (line[0] == 'C' && line[1] == ' ')
		parse_rgb(line, C_C, data, &data->texture.ceiling);
	else if (line[0] == 0)
		return ;
	else if (ft_isdigit(line[0]) || line[0] == ' ')
		data->check[MAP_CHECK] = 1;
	else
		exit_process(data, CUB_DATA_CORRUPTED);
}

void	parse_cub_data(t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	if ((fd = open(data->cub_path, O_RDONLY)) < 0)
		exit_process(data, CANT_OPEN_FILE);
	while (get_next_line(fd, &line))
	{
		parse_info(line, data);
		if (data->check[MAP_CHECK] == 1)
			valid_map(line, data);
		ft_free(line);
	}
	parse_info(line, data);
	if (data->check[MAP_CHECK] == 1)
		valid_map(line, data);
	ft_free(line);
	ft_free(data->cub_path);
	close(fd);
	i = -1;
	while (++i < 10)
	{
		if (data->check[i] != 1)
			exit_process(data, CUB_DATA_CORRUPTED);
	}
}
