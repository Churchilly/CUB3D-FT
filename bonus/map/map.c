/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:55:41 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 23:11:55 by yusudemi         ###   ########.fr       */
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
		printf("[%s] -> shown as [%s] (validated: %d)\n", 
			files[i].file, 
			files[i].file_shown ? files[i].file_shown : "NULL",
			files[i].validated);
		i++;
	}
	printf("--END OF MAP FILES--\n");
}

static void	parse_normalized_files(t_map_file *files)
{
	int		i;
	char	*fname;
	int		fname_len;
	int		base_len;
	int		ext_len;

	i = 0;
	ext_len = ft_strlen(MAP_FORMAT); // ".cub" = 4
	while (files && files[i].file)
	{
		// Get filename without folder path
		fname = files[i].file + ft_strlen(MAP_FOLDER);
		fname_len = ft_strlen(fname);
		
		// If filename fits within MAP_MAX_LEN, use it as-is
		if (fname_len <= MAP_MAX_LEN)
		{
			files[i].file_shown = alloc_crit(fname_len + 1);
			strcpy(files[i].file_shown, fname);
		}
		else
		{
			base_len = MAP_MAX_LEN - ext_len - 1; // -1 for the '*'
			
			files[i].file_shown = alloc_crit(MAP_MAX_LEN + 1);
			strncpy(files[i].file_shown, fname, base_len);
			files[i].file_shown[base_len] = '\0';
			strcat(files[i].file_shown, "*");
			strcat(files[i].file_shown, MAP_FORMAT);
		}
		i++;
	}
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
	parse_normalized_files(map->files);
	closedir(dir);
	debug_printer_files(map->files);
}
