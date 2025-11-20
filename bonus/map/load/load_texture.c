/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 07:52:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 02:09:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


static char	*extract_texture_path(char *path_start, t_main *g)
{
	char	*path_end;
	char	*path;
	int		path_len;
	int		i;

	path_start += 2;
	while (*path_start && is_space(*path_start))
		path_start++;
	path_end = path_start;
	while (*path_end && !is_space(*path_end) && *path_end != '\n')
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
	{
		map_cleanup_exit("Error: Missing texture file", g);
		return (NULL);
	}
	path = alloc_crit(path_len + 1);
	if (!path)
	{
		map_cleanup_exit("Error: Memory allocation failed", g);
		return (NULL);
	}
	i = -1;
	while (++i < path_len)
		path[i] = path_start[i];
	path[i] = '\0';
	return (path);
}

static int	check_file_extension(char *path, t_main *g)
{
	int		path_len;
	int		fd;

	path_len = strlen(path);
	if (path_len < 4)
	{
		map_cleanup_exit("Error: Invalid texture file path", g);
		return (0);
	}
	printf("path: [%s]\n", path);
	if (strcmp(path + path_len - 4, ".xpm") != 0)
	{
		map_cleanup_exit("Error: Texture file must have .xpm extension", g);
		return (0);
	}

	// Check if file exists and is readable
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		map_cleanup_exit("Error: Cannot open texture file", g);
		return (0);
	}
	close(fd);
	printf("Texture file exists and is readable: %s\n", path);
	return (1);
}

static int	set_texture(t_texture *target, char *path, t_main *g)
{
	printf("Attempting to load texture: [%s]\n", path);
	target->img = mlx_xpm_file_to_image(g->window.mlx, path,
		&target->width, &target->height);
	if (!target->img)
	{
		map_cleanup_exit("Error: Failed to load texture image", g);
		return (0);
	}
	target->addr = mlx_get_data_addr(target->img,
		&target->bits_per_pixel, &target->line_length,
		&target->endian);
	if (!target->addr)
	{
		map_cleanup_exit("Error: Failed to get texture data address", g);
		return (0);
	}
	printf("Successfully loaded texture: %dx%d pixels\n",
		target->width, target->height);
	return (1);
}

void	load_texture(char *raw_map, t_texture *target, char *identifier, t_main *g)
{
	char	*path;

	printf("Parsing texture: %s\n", identifier);
	if (target->img)
	{
		map_cleanup_exit("Error: Duplicate texture identifier", g);
		return ;
	}
	path = extract_texture_path(raw_map, g);
	if (!path || g->state == MENU_ERROR)
		return ;
	if (!check_file_extension(path, g) || g->state == MENU_ERROR)
		return ;
	if (!set_texture(target, path, g) || g->state == MENU_ERROR)
		return ;
	printf("Successfully parsed texture: %s\n", identifier);
}
