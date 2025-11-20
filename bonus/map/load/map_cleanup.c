/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:02:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 18:15:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "../../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

void	map_cleanup(t_main *game)
{
	// in map struct clear everything except files!!
	printf("duck\n");
	if (game->window.mlx)
	{
		printf("fuck1\n");
		if (game->map.texture_no.img)
		{
			mlx_destroy_image(game->window.mlx, game->map.texture_no.img);
			game->map.texture_no.img = NULL;
		}
		printf("fuck2\n");
		if (game->map.texture_so.img)
		{
			mlx_destroy_image(game->window.mlx, game->map.texture_so.img);
			game->map.texture_so.img = NULL;
		}
		printf("fuck3\n");
		if (game->map.texture_we.img)
		{
			mlx_destroy_image(game->window.mlx, game->map.texture_we.img);
			game->map.texture_we.img = NULL;
		}
		printf("fuck4\n");
		if (game->map.texture_ea.img)
		{
			mlx_destroy_image(game->window.mlx, game->map.texture_ea.img);
			game->map.texture_ea.img = NULL;
		}
		printf("fuck5\n");
		if (game->map.texture_f.img)
		{
			mlx_destroy_image(game->window.mlx, game->map.texture_f.img);
			game->map.texture_f.img = NULL;
		}
	}
	printf("duck2\n");
	game->map.color_c = 0;
	game->map.next_map = NULL;
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.mana = MAX_MANA;
	game->map.player.health = MAX_HEALTH;
	int	i;
	printf("duck3\n");
	if (game->map.matrix)
	{
		i = -1;
		while (game->map.matrix[++i])
		{
			free(game->map.matrix[i]);
		}
		free(game->map.matrix);
		game->map.matrix = NULL;
	}
	printf("duck5555555555\n");
}

// cleanup and show error menu instead of exiting
void	map_cleanup_exit(char *errmsg, t_main *game)
{
	printf("%s\n", errmsg);
	map_cleanup(game);
	game->state = MENU_ERROR;
}