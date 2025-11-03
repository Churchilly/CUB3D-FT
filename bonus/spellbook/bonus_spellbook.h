/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:39 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/03 15:59:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SPELLBOOK_H
# define BONUS_SPELLBOOK_H

# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"

typedef enum e_spell		t_spell;
typedef struct s_spellbook	t_spellbook;

enum	e_spell
{
	FIREBALL = 0,
	LOCK,
	UNLOCK,
	BARRIER,
};

struct s_spellbook
{
	t_spell		current;
	t_vector	win_pos;
	t_vector	target_win_pos;
	t_cub3_image	img;
};

#endif