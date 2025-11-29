/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 07:52:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:30:07 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*extract_texture_path(char *path_start)
{
	char	*path_end;
	char	*path;
	int		path_len;
	int		i;

	path_start += 2;
	while (*path_start && isspace(*path_start))
		path_start++;
	path_end = path_start;
	while (*path_end && !isspace(*path_end))
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
		return (NULL);
	path = alloc(path_len + 1, TEMPORARY);
	i = -1;
	while (++i < path_len)
		path[i] = path_start[i];
	return (path);
}

static int	check_file_extension(char *path)
{
	int	path_len;
	int	fd;

	path_len = strlen(path);
	if (path_len < 4)
		return (1);
	if (strcmp(path + path_len - 4, ".xpm") != 0)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

static int	set_texture(t_texture *target, char *path, t_main *g)
{
	target->img = mlx_xpm_file_to_image(g->window.mlx, path, &target->width,
			&target->height);
	if (!target->img)
		return (1);
	target->addr = mlx_get_data_addr(target->img, &target->bits_per_pixel,
			&target->line_length, &target->endian);
	if (!target->addr)
		return (1);
	return (0);
}

int	load_texture(char *raw_map, t_texture *target, t_main *g)
{
	char	*path;

	if (target->img)
		return (1);
	path = extract_texture_path(raw_map);
	if (!path)
		return (1);
	if (check_file_extension(path))
		return (1);
	if (set_texture(target, path, g))
		return (1);
	return (0);
}
