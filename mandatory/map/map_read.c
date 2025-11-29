/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:41:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 23:04:42 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gc/gc.h"
#include "../main/main.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*reader(int fd)
{
	char	*raw_map;
	char	*tmp;
	char	read_buffer[10000];
	int		bytes_read;

	raw_map = alloc_crit(1);
	if (!raw_map)
	{
		close(fd);
		return (printf("Error: Memory allocation failed\n"), NULL);
	}
	raw_map[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, sizeof(read_buffer) - 1);
		if (bytes_read == -1)
			return (printf("Error: Error while reading file\n"), NULL);
		read_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(raw_map, read_buffer);
		if (!tmp)
			return (printf("Error: Memory allocation failed\n"), NULL);
		raw_map = tmp;
	}
	return (raw_map);
}

static int	validate_extension(char *map_loc)
{
	int	len;

	len = ft_strlen(map_loc);
	if (len < 4 || ft_strncmp(map_loc + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

char	*cub_map_read(char *map_file)
{
	char	*raw_map;
	int		fd;

	if (!validate_extension(map_file))
		return (printf("Error: cub map must have .cub extension\n"), NULL);
	fd = open(map_file, O_RDONLY, 0666);
	if (fd == -1)
	{
		printf("Error: Cannot open map file %s\n", map_file);
		return (NULL);
	}
	raw_map = reader(fd);
	close(fd);
	if (!raw_map)
		return (printf("Error: Failed to read map file\n"), NULL);
	return (raw_map);
}
