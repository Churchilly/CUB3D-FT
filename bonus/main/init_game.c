/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:10:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 18:24:21 by yusudemi         ###   ########.fr       */
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
	printf("here\n");
	map_cleanup(game);
	printf("here\n");
	load_map(map_file, game);
	if (game->state == MENU_ERROR)
		return ;
	printf("here1\n");
	cub_objects(game);
	printf("here2\n");
	cub_spellbook(&game->spellbook, game->window.mlx);
	printf("here3\n");
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);

	printf("here4\n");
}