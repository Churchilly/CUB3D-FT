/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:10:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/22 05:21:34 by root             ###   ########.fr       */
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
#include <X11/Xlib.h>
#include "../minilibx/mlx_int.h"

void	init_game(t_main *game, char *map_file)
{
	clear_section(DYNAMIC);
	create_barriers(game);
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.mana = MAX_MANA;
	game->map.player.health = MAX_HEALTH;
	game->map.next_map = NULL;
	game->map.color_c = -1;
	game->map.texture_ea.img = NULL;
	game->map.texture_no.img = NULL;
	game->map.texture_ea.img = NULL;
	game->map.texture_ea.img = NULL;
	game->map.texture_f.img = NULL;
	if (load_map(map_file, game))
		game->state = MENU_ERROR;
	else
		init_minimap(game);
}