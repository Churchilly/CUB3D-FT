/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 15:36:04 by btuncer          ###   ########.fr       */
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
