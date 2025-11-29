/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:41:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:30:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*reader(int fd)
{
	char	*raw_map;
	char	*tmp;
	char	read_buffer[10000];
	int		bytes_read;

	raw_map = alloc(1, TEMPORARY);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, sizeof(read_buffer) - 1);
		if (errno == EINTR)
			continue ;
		if (bytes_read == -1)
			return (NULL);
		read_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(raw_map, read_buffer, TEMPORARY);
		raw_map = tmp;
	}
	return (raw_map);
}

char	*read_file(char *map_file)
{
	char	*raw_map;
	int		fd;

	fd = open(map_file, O_RDONLY, 0666);
	if (fd == -1)
		return (NULL);
	raw_map = reader(fd);
	close(fd);
	if (!raw_map)
		return (NULL);
	return (raw_map);
}
