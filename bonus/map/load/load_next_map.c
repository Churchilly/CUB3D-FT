/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_next_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:36:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 15:23:18 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <ctype.h>

void	load_next_map_info(char *raw_map, t_main *game)
{
	char	*path_start;
	char	*path_end;
	int		path_len;
	int		i;

	path_start = raw_map + 4;
	while (*path_start && isspace(*path_start))
		path_start++;
	path_end = path_start;
	while (*path_end && !isspace(*path_end))
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
	{
		game->map.next_map = NULL;
		return ;
	}
	game->map.next_map = alloc(path_len + 1, DYNAMIC);
	i = -1;
	while (++i < path_len)
		game->map.next_map[i] = path_start[i];
}
