/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:51:08 by root              #+#    #+#             */
/*   Updated: 2025/11/26 21:58:02 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# define GOLD_COLOR 0xFFD700

// MINIMAP DEFINES
# define MMAP_GRID_SIZE 20
# define MMAP_GRID_COUNT 9
# define MMAP_RANGE 5
# define MMAP_MARGIN 10

# define MMAP_PLAYER_IMAGE_OFFSET 90.0

// PLAYER STATS DEFINES
# define MANA_COLOR 0xff2757f5
# define MANA_POS_X 20
# define MANA_POS_Y 255
# define MANA_CRIT_VAL 40.0
# define MAX_MANA 150.0

# define HEALTH_COLOR 0xffff2424
# define HEALTH_POS_X 20
# define HEALTH_POS_Y 225
# define HEALTH_CRIT_VAL 50.0
# define MAX_HEALTH 175.0

# define CRIT_STAT_COLOR 0xff502370

# define POTIONS_POS_X 720
# define POTIONS_POS_Y 60
# define POTION_GAP -10

# define MAP_SELECT_PAGE_NUM 8

# include "../minilibx/mlx.h"
# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"
#include "../cub3_fonts/cub3_fonts.h"
# include <stdbool.h>

typedef struct s_button			t_button;
typedef struct s_text_button	t_text_button;
typedef struct s_main_menu		t_main_menu;
typedef struct s_map_select		t_map_select;
typedef struct s_shop			t_shop;
typedef struct s_game_summary	t_game_summary;
typedef struct s_error			t_error;
typedef struct s_main			t_main;
typedef enum e_button_type		t_button_type;

struct s_button
{
	t_im		image;
	t_vector	position;
	int			width;
	int			height;
};

struct s_text_button
{
	t_vector	position;
	int			width;
	int			height;
	t_text		text_data;
};

struct s_main_menu
{
	t_button		*selected;
	t_button		btn_continue;
	t_button		btn_campaign;
	t_button		btn_map_select;
	t_button		btn_exit;
};

struct s_map_select
{
	t_text_button	*selected;
	t_text_button	**maps;
	int				curr_page;
	t_text_button	next_page;
	t_text_button	prev_page;
};

struct s_shop
{
	t_text_button		*selected;
	t_text_button	items[6];
	t_text_button	to_continue;
};

struct s_game_summary
{
	t_text			run_time;
	t_text			kill_count;
	t_text			total_income;
	t_text			items_bought;
	t_text			to_continue;
};

struct s_error
{
	t_text			error_text;
	t_text			to_continue;
};


void	draw_minimap(t_main *game);
void	draw_mmap(t_main *g);
void	init_minimap(t_main *g);

void	*init_main_menu(t_main *g, t_main_menu *mmenu);
void	*init_map_select_menu(t_main *g, t_map_select *menu);
void	*init_error_menu(t_main *g, t_error *menu);
void	*init_shop_menu(t_main *g, t_shop *menu);
void	*init_game_summary_menu(t_main *g, t_game_summary *menu);
void	switch_menu(t_main *g);

void	*set_button(t_button *button, t_im *img, t_vector pos);
void	check_button(t_main *game, t_button *button);
void	place_button(t_main *g, t_button *btn);
void	*set_text_button(t_text_button *button, t_text text_data, t_vector pos);
void	check_text_button(t_main *game, t_text_button *button);
void	place_text_button(t_main *g, t_text_button *button, char *label);

// General button navigation (delegates to specific menu functions)
void	activate_button(t_main *g);
void	next_button(t_main *game);
void	prev_button(t_main *game);
void	next_page(t_main *game);
void	prev_page(t_main *game);

// Main/Pause menu specific
void	next_main_pause_item(t_main *g);
void	prev_main_pause_item(t_main *g);
void	activate_button_main_pause(t_main *g);

// Map select menu specific
void	next_map_select_item(t_main *g);
void	prev_map_select_item(t_main *g);
void	activate_button_map_select(t_main *g);

// Shop menu specific
void	next_shop_item(t_main *g);
void	prev_shop_item(t_main *g);
void	activate_button_shop(t_main *g);

// Player stats
void	draw_mana_bar(t_main *g);
void	draw_heath_bar(t_main *g);
void draw_potions(t_main *g);
void draw_currency_game(t_main *g);

// Button event navigations
void	new_game(t_main *g, char *map_file);
void	next_map(t_main *g);

#endif

