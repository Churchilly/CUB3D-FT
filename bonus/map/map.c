/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:55:41 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/18 23:35:57 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "map.h"
#include <stddef.h>
#include "../gc/gc.h"
#include <string.h>

static int	validate_extension(char	*file_name)
{
	int	len;

	len = strlen(file_name);
	if (len < 4 || strcmp(file_name + len - 4, MAP_FORMAT) != 0)
		return (0);
	return (1);
}

static int	count_valid_files(DIR *dir)
{
	struct dirent	*entry;
	int				entry_len;
	int				count;

	entry = readdir(dir);
	count = 0;
	while (entry)
	{
		entry_len = strlen(entry->d_name);
		if (validate_extension(entry->d_name))
			count++;
		entry = readdir(dir);
	}
	if (count == 0)
	{
		printf("Error: No valid map files");
		exit(1);
	}
	return (count);
}

static void	parse_valid_files(DIR *dir, t_map_file **files, int count)
{
	struct dirent	*entry;
	int				entry_len;
	int				i;

	*files = alloc_crit(sizeof(t_map_file) * (count + 1));
	entry = readdir(dir);
	i = 0;
	while (entry)
	{
		entry_len = strlen(entry->d_name);
		if (validate_extension(entry->d_name))
		{
			(*files)[i].file = alloc_crit(ft_strlen(MAP_FOLDER) + entry_len + 1);
			strcpy((*files)[i].file, MAP_FOLDER);
			strcat((*files)[i].file, entry->d_name);
			(*files)[i].validated = 0;
			i++;
		}
		entry = readdir(dir);
	}
	(*files)[i].file = NULL;
	(*files)[i].validated = 0;
}

static void debug_printer_files(t_map_file *files)
{
	int	i;

	printf("MAP FILES:\n");
	i = 0;
	while (files && files[i].file)
	{
		printf("[%s] (validated: %d)\n", files[i].file, files[i].validated);
		i++;
	}
	printf("--END OF MAP FILES--\n");
}

void	cub_map(t_map *map)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;
	int				i;

	dir = opendir(MAP_FOLDER);
	if (!dir)
	{
		printf("Error: Cannot open map folder\n");
		exit(1);
	}
	count = count_valid_files(dir);
	rewinddir(dir);
	parse_valid_files(dir, &map->files, count);
	closedir(dir);
	debug_printer_files(map->files);
}
