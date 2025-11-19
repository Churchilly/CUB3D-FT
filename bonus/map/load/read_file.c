/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:41:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/18 19:56:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>   // Added: for printf function
#include <string.h>  // Added: for strlen and strcmp functions
#include "../../main/main.h"


static char	*reader(int fd)
{
	char	*raw_map;
	char	*tmp;
	char	read_buffer[10000];
	int		bytes_read;

	raw_map = alloc_crit(1);
	if (!raw_map)
	{
		printf("Error: Memory allocation failed\n");
		close(fd);
		return (NULL);
	}
	raw_map[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, sizeof(read_buffer) -1);
		if (bytes_read == -1)
		{
			// free(raw_map); HERE1
			printf("Error: Encountered an error while reading file\n");
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(raw_map, read_buffer);
		// free(raw_map); HERE1
		if (!tmp)
		{
			printf("Error: Memory allocation failed\n");
			return (NULL);
		}
		raw_map = tmp;
	}
	return (raw_map);
}


// for efficiency i read all map data at once. dont touch! line by line reading is absurt
char	*read_file(char	*map_file)
{
	char	*raw_map;
	int		fd;

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

