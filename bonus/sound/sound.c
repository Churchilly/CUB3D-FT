/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:32 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/06 14:58:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"
#include "../gc/gc.h"
# define MINIAUDIO_IMPLEMENTATION
# define MA_NO_WAV
# define MA_NO_FLAC
# include "miniaudio.h"

void	play_walk()
{
	return ;
}

void	sound(t_sound sound)
{
	static ma_engine	*engine = 0;
	ma_result			result;
x
	if (sound == SOUND_INIT)
	{
		engine = malloc(sizeof(ma_engine)); // i didnt use gc here and its intended xd
		if (!engine)
			exit(1);
		result = ma_engine_init(NULL, engine);
		if (result != MA_SUCCESS)
			exit(1);
	}
	else if (sound == SOUND_FIREBALL)
	{
		result = ma_engine_play_sound(engine, "sound/sound_effects/fire-magic-6-378641.mp3", NULL);
		if (result != MA_SUCCESS)
			printf("Failed to play sound\n");
	}
	else if (sound == SOUND_WALK)
	{
		result = ma_engine_play_sound(engine, "sound/sound_effects/fire-magic-6-378641.mp3", NULL);
		if (result != MA_SUCCESS)
			printf("Failed to play sound\n");
	}
	else if (sound == SOUND_DOOR_OPEN)
	{
		result = ma_engine_play_sound(engine, "sound/sound_effects/fire-magic-6-378641.mp3", NULL);
		if (result != MA_SUCCESS)
			printf("Failed to play sound\n");
	}
	else if (sound == SOUND_DOOR_CLOSE)
	{
		result = ma_engine_play_sound(engine, "sound/sound_effects/fire-magic-6-378641.mp3", NULL);
		if (result != MA_SUCCESS)
			printf("Failed to play sound\n");
	}
	else if (sound == SOUND_UNINIT)
	{
		ma_engine_uninit(engine);
		free(engine);
		engine = 0;
	}
	else
		printf("FUCK YOU!\n");
}
