/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/12 21:54:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
#include "../gc/gc.h"
#include "../player/player.h"
#include "../events/events.h"

#include <X11/keysym.h>

__attribute__((destructor))
void cya(void)
{
	dump_crit_gc();
	printf("sound cleanup start\n");
	printf("sound cleanup end\n");
}

int main(int argc, char **argv)
{
	t_main game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return 1;
	}
	__init__(&game);
	cub_map(argv[1], &game); // game  goes here because i need to use mlx connection to convert textures
	cub_objects(&game); // creates objects
	cub_create_window(&game); // game goes here for memory management stuff 
	dump_gc();
	cub_render(&game); // add the render and its done easy right
	_init_hooks(&game);
	center_window(&game);
	mlx_loop(game.window.mlx);
	map_cleanup(&game);
	return 0;
}
