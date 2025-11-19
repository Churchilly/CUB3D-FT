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


static char	*extract_texture_path(char *path_start)
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
		printf("Error: Missing texture file\n");
		exit(1);
	}
	path = alloc_crit(path_len + 1);
	if (!path)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	i = -1;
	while (++i < path_len)
		path[i] = path_start[i];
	path[i] = '\0';
	return (path);
}

static void	check_file_extension(char *path)
{
	int		path_len;
	int		fd;

	path_len = strlen(path);
	if (path_len < 4)
	{
		printf("Error: Invalid texture file path\n");
		exit(1);
	}
	printf("path: [%s]\n", path);
	if (strcmp(path + path_len - 4, ".xpm") != 0)
	{
		printf("Error: Texture file must have .xpm extension\n");
		exit(1);
	}
	
	// Check if file exists and is readable
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open texture file: %s\n", path);
		exit(1);
	}
	close(fd);
	printf("Texture file exists and is readable: %s\n", path);
}

static void	set_texture(t_texture *target, char *path, t_main *g)
{
	printf("Attempting to load texture: [%s]\n", path);
	target->img = mlx_xpm_file_to_image(g->window.mlx, path, 
		&target->width, &target->height);
	if (!target->img)
	{
		printf("Error: Failed to load texture image from path: %s\n", path);
		exit(1);
	}
	target->addr = mlx_get_data_addr(target->img,
		&target->bits_per_pixel, &target->line_length,
		&target->endian);
	if (!target->addr)
	{
		printf("Error: Failed to get texture data address\n");
		exit(1);
	}
	printf("Successfully loaded texture: %dx%d pixels\n", 
		target->width, target->height);
}

void	load_texture(char *raw_map, t_texture *target, char *identifier, t_main *g)
{
	char	*path;

	printf("Parsing texture: %s\n", identifier);
	if (target->img)
	{
		printf("Error: Duplicate texture identifier: %s\n", identifier);
		exit(1);
	}
	path = extract_texture_path(raw_map);
	check_file_extension(path);
	set_texture(target, path, g);
	printf("Successfully parsed texture: %s\n", identifier);
}
