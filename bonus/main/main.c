/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 21:36:24 by yusudemi         ###   ########.fr       */
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


/*
	Game initialization system:
	- __init__() - Initializes MLX, window, gallery, menu, spellbook
	- init_game() - Initializes map, objects, raycasting (called from campaign button)
	
	No command-line map argument needed anymore!
	Maps are loaded through the menu system.
*/

int main(void)
{
	t_main game;

	__init__(&game);

	cub_create_window(&game);

	dump_gc();
	loop_event(&game);
	
	// Setup event hooks and start main loop
	_init_hooks(&game);
	center_window(&game);
	mlx_loop(game.window.mlx);
	
	// Cleanup
	map_cleanup(&game);
	return 0;
}
