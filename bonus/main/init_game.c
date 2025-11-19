/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:10:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 02:11:27 by yusudemi         ###   ########.fr       */
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
#include <X11/Xlib.h>
#include "../minilibx/mlx_int.h"


void	init_game(t_main *game, char *map_file)
{
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.mana = MAX_MANA;
	game->map.player.health = MAX_HEALTH;
	
	load_map(map_file, game);
	cub_objects(game);
	cub_spellbook(&game->spellbook, game->window.mlx);
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);
}