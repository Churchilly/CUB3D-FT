/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:55:41 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 04:54:35 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "map.h"
#include <string.h>
#include "../garbage_collector/garbage_collector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
	int				count;

	entry = readdir(dir);
	count = 0;
	while (entry)
	{
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

	*files = alloc(sizeof(t_map_file) * (count + 1), STATIC);
	entry = readdir(dir);
	i = 0;
	while (entry)
	{
		entry_len = strlen(entry->d_name);
		if (validate_extension(entry->d_name))
		{
			(*files)[i].file = alloc(strlen(MAP_FOLDER) + entry_len + 1,
					STATIC);
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

static void	parse_normalized_files(t_map_file *files)
{
	int		i;
	char	*fname;
	int		fname_len;
	int		base_len;
	int		ext_len;

	i = -1;
	while (files && files[++i].file)
	{
		fname = files[i].file + strlen(MAP_FOLDER);
		fname_len = strlen(fname);
		if (fname_len <= MAP_MAX_LEN)
		{
			files[i].file_shown = alloc(fname_len + 1, STATIC);
			strcpy(files[i].file_shown, fname);
		}
		else
		{
			base_len = MAP_MAX_LEN - strlen(MAP_FORMAT) - 1;
			files[i].file_shown = alloc(MAP_MAX_LEN + 1, STATIC);
			strncpy(files[i].file_shown, fname, base_len);
			strcat(files[i].file_shown, "*");
			strcat(files[i].file_shown, MAP_FORMAT);
		}
	}
}

void	cub_map(t_map *map)
{
	DIR				*dir;
	int				count;

	dir = opendir(MAP_FOLDER);
	if (!dir)
	{
		printf("Error: Cannot open map folder\n");
		exit(1);
	}
	count = count_valid_files(dir);
	rewinddir(dir);
	parse_valid_files(dir, &map->files, count);
	parse_normalized_files(map->files);
	closedir(dir);
}
