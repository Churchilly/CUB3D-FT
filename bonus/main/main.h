/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 23:08:28 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../map/map.h"
# include "../player/player.h"

# include "window.h"

# include "../render/render.h"
# include "../render/render_ray_list.h"

# include "../hud/hud.h"
# include "../cub3_images/cub3_images.h"
# include "../cub3_fonts/cub3_fonts.h"

# include "../objects/bonus_fireball.h"
# include "../objects/bonus_enemy.h"
# include "../objects/bonus_objects.h"
# include "../objects/bonus_orbs.h"

# include "../spellbook/bonus_spellbook.h"

# include "../objects/doors.h"

# include <stdbool.h>

# include "../sound/sound.h"

typedef struct s_key_list	t_key_list;
typedef struct s_main		t_main;
typedef struct s_switch_key	t_switch_key;
typedef enum e_game_state	t_game_state;

enum e_game_state
{
	MENU_MAIN = 0,
	GAME,
	MENU_PAUSE,
	MENU_MAP_SELECT,
	MENU_SHOP
};

struct s_switch_key
{
	int key;
	int key_switch;
};

struct s_key_list
{
	bool w;
	bool a;
	bool s;
	bool d;
	int arrow_l;
	int arrow_r;
	t_switch_key e;
	t_switch_key q;
	t_switch_key spc;
	t_switch_key f3;
};

struct s_main
{
	t_game_state	state; // change this. this should store the current state -> main_menu - pause_menu - game - shop - map_select
	t_map			map;
	t_window		window;
	t_ray_list		rays;
	t_obj_list		objects;
	t_spellbook		spellbook;
	t_key_list		key_list;
	t_cub3_gallery	gallery;
	t_main_menu		main_menu;
	t_map_select	map_select;
	t_font_menu font_menu;
};

void	__init__(t_main *game);
void	init_game(t_main *game, char *map_file);
void _init_hooks(t_main *game);
void center_window(t_main *g);
long long	current_time_ms(void);

#endif