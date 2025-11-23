/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/22 07:29:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
#include "../player/player.h"
#include "../events/events.h"

#include <X11/keysym.h>

__attribute__((destructor))
void cya(void)
{
	printf("cleanup start\n");
	clear_section(ALL);
	
	printf("cleanup end\n");
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
	t_collector	gc;

	init_collector(&gc, &(game));
	__init__(&game);
	cub_create_window(&game);
	loop_event(&game);
	_init_hooks(&game);
	center_window(&game);
	mlx_loop(game.window.mlx);
	return 0;
}
