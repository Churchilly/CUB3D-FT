/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:02:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 22:52:34 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	map_cleanup(t_main *game)
{
	if (game->window.mlx)
	{
		if (game->map.texture_no.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_no.img);
		if (game->map.texture_so.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_so.img);
		if (game->map.texture_we.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_we.img);
		if (game->map.texture_ea.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_ea.img);
	}
}

void	map_cleanup_exit(char *errmsg, t_main *game)
{
	printf("%s\n", errmsg);
	map_cleanup(game);
	exit(1);
}
