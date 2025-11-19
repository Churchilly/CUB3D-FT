/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 00:11:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SOUND_H
# define BONUS_SOUND_H


// use -> system(AUDIO_FIREBALL)

typedef enum e_sound	t_sound;

# define AUDIO_FIREBALL "aplay -q sound/sound_effects/fireball-1.wav > /dev/null 2>&1 &"
# define AUDIO_FIREBALL_2 "aplay -q sound/sound_effects/fireball-2.wav > /dev/null 2>&1 &"
# define AUDIO_FIREBALL_8BIT "aplay -q sound/sound_effects/fireball-8bit.wav > /dev/null 2>&1 &"
# define AUDIO_FIREBALL_XD "aplay -q sound/sound_effects/fireball-xd.wav > /dev/null 2>&1 &"
# define AUDIO_ALOHOMORA "aplay -q sound/sound_effects/alohomora.wav > /dev/null 2>&1 &"
# define AUDIO_COLLOPORTUS "aplay -q sound/sound_effects/colloportus.wav > /dev/null 2>&1 &"
# define AUDIO_DOOR_OPEN "aplay -q sound/sound_effects/door-open.wav > /dev/null 2>&1 &"
# define AUDIO_DOOR_CLOSE "aplay -q sound/sound_effects/door-close.wav > /dev/null 2>&1 &"
# define AUDIO_FOOTSTEP_1 "pplay -q sound/sound_effects/footstep-1.wav > /dev/null 2>&1 &"
# define AUDIO_FOOTSTEP_2 "aplay -q sound/sound_effects/footstep-2.wav > /dev/null 2>&1 &"
# define AUDIO_FOOTSTEP_3 "aplay -q sound/sound_effects/footstep-3.wav > /dev/null 2>&1 &"
# define AUDIO_MAIN_MENU "aplay -q sound/sound_effects/open_main_menu.wav > /dev/null 2>&1 &"

# define AUDIO_MUSIC "aplay -q sound/music/background.wav > /dev/null 2>&1 &"
#endif
