/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:46:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

__attribute__((destructor)) void	cya(void)
{
	clear_section(ALL);
}

int	main(void)
{
	t_main		game;
	t_collector	gc;

	init_collector(&gc, &(game));
	__init__(&game);
	cub_create_window(&game);
	loop_event(&game);
	_init_hooks(&game);
	center_window(&game);
	mlx_loop(game.window.mlx);
	return (0);
}
