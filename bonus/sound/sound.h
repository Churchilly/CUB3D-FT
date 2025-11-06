/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/06 12:54:19 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SOUND_H
# define BONUS_SOUND_H

typedef enum e_sound	t_sound;

enum	e_sound
{
	SOUND_INIT = 0,
	SOUND_UNINIT = 0,
	SOUND_FIREBALL,
	SOUND_WALK,
	SOUND_DOOR_OPEN,
	SOUND_DOOR_CLOSE,
};

void	sound(t_sound sound);

#endif