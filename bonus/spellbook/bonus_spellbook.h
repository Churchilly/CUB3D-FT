/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:39 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/06 14:31:56 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SPELLBOOK_H
# define BONUS_SPELLBOOK_H

# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"

# define SPELL_COOLDOWN 60
# define SPELLBOOK_ANIM_SPEED 12.0
# define SPELLBOOK_IDLE_ANIM_SPEED 0.1
# define SPELLBOOK_SCALE 3.0

typedef enum e_spell		t_spell;
typedef struct s_spellbook	t_spellbook;

enum	e_spell
{
	FIRBALL = 0,
	LOCK,
	UNLOCK,
	BARRIER
};

struct s_spellbook
{
	t_spell			current;
	t_texture		*cur_texture; // tmp
	t_vector		win_pos;
	t_cub3_image	img_fireball; // [BURAK]
	t_cub3_image	img_lock;
	t_cub3_image	img_unlock;
	int				cooldown;
	int				changing_direction; // next = 1, prev = -1, idle = 0
};

typedef struct s_main	t_main;

void	next_spell(t_main *g);
void	prev_spell(t_main *g);
void	cast_spell(t_main *g);
void	cast_lock(t_main *g);
void	cast_unlock(t_main *g);
void	cast_fireball(t_main *g);
void	animate_spellbook(t_main *g);
void	render_spellbook(t_main *g);

#endif