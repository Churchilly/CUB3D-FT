/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:05:26 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 03:56:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stddef.h>
# include "../main/window.h"

typedef enum e_section				t_section;
typedef struct s_gc_node			t_gc_node;
typedef struct s_garbage_collector	t_collector;

enum e_section
{
	ALL,
	STATIC,
	DYNAMIC,
	TEMPORARY,
	WINDOW
};

struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
};

struct	s_garbage_collector
{
	t_gc_node	*static_section;
	t_gc_node	*dynamic_section;
	t_gc_node	*temporary_section;
	t_window	*win;
};

void		init_collector(t_collector *gc, t_window *win);
void		*alloc(size_t size, t_section section);
void		clear_section(t_section section);

void		**get_section(t_section section);
t_collector	*pointer_storage(void *ptr);

#endif