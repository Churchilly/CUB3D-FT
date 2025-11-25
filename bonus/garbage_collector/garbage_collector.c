/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:05:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 18:39:15 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <strings.h>
#include "../main/main.h"

t_collector	*pointer_storage(void *ptr)
{
	static t_collector *collector = NULL;

	if (ptr)
		collector = ptr;
	return (collector);
}

void	**get_section(t_section section)
{
	t_collector	*gc;

	gc = pointer_storage(NULL);
	if (!gc)
		return (NULL);
	if (section == STATIC)
		return ((void **)&gc->static_section);
	if (section == DYNAMIC)
		return ((void **)&gc->dynamic_section);
	if (section == TEMPORARY)
		return ((void **)&gc->temporary_section);
	if (section == WINDOW)
		return ((void **)&gc->win);
	if (section == D_TEXTURES)
		return ((void **)gc->d_textures);
	if (section == S_TEXTURES)
		return ((void **)gc->s_textures);
	return (NULL);
}

void	init_collector(t_collector *gc, t_main *g)
{
	bzero(gc, sizeof(t_collector));
	pointer_storage(gc);
	gc->win = &(g->window);
	gc->d_textures[0] = &(g->map.texture_ea.img);
	gc->d_textures[1] = &(g->map.texture_we.img);
	gc->d_textures[2] = &(g->map.texture_so.img);
	gc->d_textures[3] = &(g->map.texture_no.img);
	gc->d_textures[4] = &(g->map.texture_f.img);
	gc->s_textures[0] = &(g->spellbook.texture_fireball.img);
	gc->s_textures[1] = &(g->spellbook.texture_lock.img);
	gc->s_textures[2] = &(g->spellbook.texture_unlock.img);
}

