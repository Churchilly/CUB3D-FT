/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_next_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:36:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/18 22:36:50 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	load_next_map_info(char *raw_map, t_main *game)
{
	char	*path_start;
	char	*path_end;
	int		path_len;
	int		i;

	path_start = raw_map + 4;
	while (*path_start && is_space(*path_start))
		path_start++;
	path_end = path_start;
	while (*path_end && !is_space(*path_end) && *path_end != '\n')
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
	{
		game->map.next_map = NULL;
		return ;
	}
	game->map.next_map = alloc_crit(path_len + 1);
	i = -1;
	while (++i < path_len)
		game->map.next_map[i] = path_start[i];
	game->map.next_map[i] = '\0';
	printf("Next map: %s\n", game->map.next_map);
}
