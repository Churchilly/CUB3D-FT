/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 22:46:53 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gc/gc.h"
#include "../minilibx/mlx.h"
#include "main.h"
#include <stdio.h>
#include <unistd.h>

__attribute__((destructor))
void	cya(void)
{
	dump_crit_gc();
}

static void	_init(t_main *game)
{
	ft_memset(game, 0, sizeof(t_main));
	game->window.mlx = mlx_init();
	safe_mlx(game->window.mlx, op_mlx);
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);
}

int	main(int argc, char **argv)
{
	t_main	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	_init(&game);
	cub_map(argv[1], &game);
	cub_create_window(&game);
	dump_gc();
	cub_render(&game, raycasting);
	mlx_loop(game.window.mlx);
	map_cleanup(&game);
	return (0);
}
