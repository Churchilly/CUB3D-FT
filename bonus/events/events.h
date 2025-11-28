/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:23 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 21:58:43 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_main		t_main;
typedef enum e_game_state	t_game_state;
typedef struct s_vector		t_vector;

typedef struct s_key_list	t_key_list;
typedef struct s_switch_key	t_switch_key;

struct						s_switch_key
{
	int						key;
	int						key_switch;
};

struct						s_key_list
{
	bool					w;
	bool					a;
	bool					s;
	bool					d;
	int						arrow_l;
	int						arrow_r;
	t_switch_key			e;
	t_switch_key			q;
	t_switch_key			spc;
	t_switch_key			f3;
};

int							onpress_event(int key, t_main *game);
void						onpress_event_game(int key, t_main *game);
int							onpress_key_menu(t_switch_key *switch_key, int key,
								t_main *game);
void						onpress_event_menu(int key, t_main *game);
int							onrelease_event(int key, t_main *game);
void						unlock_switch(t_main *game);

void						center_mouse(t_main *game);
void						read_mouse_movements(t_main *game);
t_vector					get_mouse_position(t_main *game);
int							mouse_click(int button, int x, int y, void *game);
void						mouse_click_shop(int x, int y, t_main *g);
void						mouse_click_map_select(int x, int y, t_main *g);
void						mouse_click_main_pause(int x, int y, t_main *g);

int							terminate_hook(void);
int							loop_event(t_main *game);
void						render_screen(t_main *game);

void						delayed_event(t_main *g, t_game_state state);

void	check_game_time(t_main *g);

#endif