/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/20 01:17:45 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "../minilibx/mlx_int.h"
#include <X11/Xlib.h>

#include <stdio.h>

void center_mouse(t_main *game)
{
    t_xvar *xvar;
    Display *display;     
    Window window_cub3d;

    xvar = (t_xvar *)game->window.mlx;
    display = xvar->display;
    window_cub3d = xvar->win_list->window;
    XWarpPointer(display, None, window_cub3d, 0, 0, 0, 0, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

t_vector get_mouse_position(t_main *game)
{
    t_xvar *xvar;
    Window cub3d;
    int win_x, win_y;
    unsigned int m;
    t_vector response;
    
    xvar = (t_xvar *)game->window.mlx;
    cub3d = xvar->win_list->window;
    XQueryPointer(xvar->display, cub3d, &cub3d, &cub3d, &win_x, &win_x, &win_x, &win_y, &m);
    response.x = win_x;
    response.y = win_y;
    return (response);
}

void read_mouse_movements(t_main *game)
{
    t_xvar *xvar;
    Window cub3d;
    int win_x, win_y;
    unsigned int m;
    int win_x_abs;
    
    xvar = (t_xvar *)game->window.mlx;
    cub3d = xvar->win_list->window;
    XQueryPointer(xvar->display, cub3d, &cub3d, &cub3d, &win_x, &win_x, &win_x, &win_y, &m);

    win_x_abs = win_x - WIN_WIDTH / 2;
    if (win_x_abs > 0)
        change_direction_advanced(game, 'R', win_x_abs);
    else if (win_x_abs < 0)
        change_direction_advanced(game, 'L', win_x_abs);
}

static bool is_xy_on_button(int x, int y, t_button *btn)
{
    if (x > btn->position.x && x < btn->position.x + btn->width)
        if (y > btn->position.y && y < btn->position.y + btn->height)
            return (true);
    return (false);
}

static bool is_xy_on_text_button(int x, int y, t_text_button *btn)
{
    if (x > btn->position.x && x < btn->position.x + btn->width)
        if (y > btn->position.y && y < btn->position.y + btn->height)
            return (true);
    return (false);
}

int mouse_click(int button, int x, int y, void *game)
{
    t_main *g;
    
    g = (t_main *)game;
    if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
    {
		if (g->main_menu.btn_continue.height != -1)
		{
        	if (is_xy_on_button(x, y, &g->main_menu.btn_continue))
            	activate_button(g);
		}
        if (is_xy_on_button(x, y, &g->main_menu.btn_campaign))
            activate_button(g);
        if (is_xy_on_button(x, y, &g->main_menu.btn_map_select))
            g->state = MENU_MAP_SELECT;
        if (is_xy_on_button(x, y, &g->main_menu.btn_exit))
            activate_button(g);
    }
	else if (g->state == MENU_MAP_SELECT)
	{
		t_text_button *page;
		int i;
		
		if (is_xy_on_text_button(x, y, &g->map_select.prev_page))
		{
			prev_page(g);
			return (0);
		}
		if (is_xy_on_text_button(x, y, &g->map_select.next_page))
		{
			next_page(g);
			return (0);
		}
		
		page = g->map_select.maps[g->map_select.curr_page];
		
		i = 0;
		while (i < MAP_SELECT_PAGE_NUM)
		{
			if (page[i].width > 0 && is_xy_on_text_button(x, y, &page[i]))
			{
				g->map_select.selected = &page[i];
				activate_button(g);
				return (0);
			}
			i++;
		}
	}
	else if (g->state == MENU_SHOP)
	{
		int i;

		if (is_xy_on_text_button(x, y, &g->shop_menu.to_continue))
		{
			g->shop_menu.selected = &g->shop_menu.to_continue;
			activate_button(g);
			return (0);
		}
		i = 0;
		while (i < 6)
		{
			if (is_xy_on_text_button(x, y, &g->shop_menu.items[i]))
			{
				g->shop_menu.selected = &g->shop_menu.items[i];
				activate_button(g);
				return (0);
			}
			i++;
		}
	}
	else if (g->state == MENU_ERROR)
	{
		/* Any click returns to main menu */
		g->state = MENU_MAIN;
	}
	else if (g->state == MENU_SUMMARY)
	{
		/* Any click returns to main menu */
		g->state = MENU_MAIN;
	}
    return (0);
}


// Bool XQueryPointer(
//     Display *display,          // X display bağlantısı
//     Window w,                  // Query yapılacak window
//     Window *root_return,       // Root window (OUT)
//     Window *child_return,      // Mouse'un üzerinde olduğu child window (OUT)
//     int *root_x, *root_y,      // Ekran (root) koordinatları (OUT)
//     int *win_x, *win_y,        // Window içi koordinatlar (OUT)
//     unsigned int *mask_return  // Mouse button ve modifier keys (OUT)
// );