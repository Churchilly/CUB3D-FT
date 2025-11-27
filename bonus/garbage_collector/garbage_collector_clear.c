/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_clear.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:05:24 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 01:11:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include "../minilibx/mlx.h"
#include "../main/main.h"

static void	clear(t_section section_name)
{
	t_gc_node	*curr;
	t_gc_node	*next;
	t_gc_node	**section;

	section = (t_gc_node **)get_section(section_name);
	if (!(*section))
		return ;
	curr = *section;
	while (curr)
	{
		next = curr->next;
		if (curr->data)
			free(curr->data);
		curr->data = NULL;
		if (curr)
			free(curr);
		curr = next;
	}
	*section = NULL;
}

static void	clear_textures(t_section sec)
{
	void	**section;
	void	*mlx;
	void	**img;
	int		i;

	section = (void ***)get_section(sec);
	mlx = ((t_window *)(*get_section(WINDOW)))->mlx;
	if (sec == D_TEXTURES)
		i = 5;
	else
		i = 3;
	while (i--)
	{
		img = (void **)((section)[i]);
		if (*img)
			mlx_destroy_image(mlx, *img);
		*img = NULL;
	}
}

static void	clear_win(void)
{
	void		**section;
	t_window	*win;

	section = get_section(WINDOW);
	if (!(*section))
		return ;
	win = (t_window *)(*section);
	if (win->mlx && win->img)
	{
		mlx_destroy_image(win->mlx, win->img);
		win->img = NULL;
	}
	if (win->mlx && win->win)
	{
		mlx_destroy_window(win->mlx, win->win);
		win->win = NULL;
	}
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		win->mlx = NULL;
	}
}

void	clear_section(t_section section_name)
{
	if (section_name == STATIC)
		clear(STATIC);
	else if (section_name == DYNAMIC)
	{
		clear(DYNAMIC);
		clear_textures(D_TEXTURES);
	}
	else if (section_name == TEMPORARY)
		clear(TEMPORARY);
	else if (section_name == ALL)
	{
		clear(STATIC);
		clear(DYNAMIC);
		clear(TEMPORARY);
		clear_textures(S_TEXTURES);
		clear_textures(D_TEXTURES);
		clear_win();
	}
}
