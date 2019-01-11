#include "Music.h"
#include <string.h>

Music* Music_Ctor(char* name)
{
	Music* music = (Music*)malloc(sizeof(Music));
	music->name = name;
	music->data = BASS_StreamCreateFile(false, ("res/music/" + name + ".mp3").c_str(), 0, 0, 0);

	music->volume = 1.0f;

	return music;
}

void Music_DCtor(Music* music)
{
	BASS_StreamFree(music->data);
	free(music);
}

void Music_play(Music* music)
{
	BASS_ChannelPlay(music->data, false);
	check_errors();
	//start_time = high_resolution_clock::now();
}

void Music_pause(Music* music)
{
	BASS_ChannelPause(music->data);
	check_errors();
}

void Music_stop(Music* music)
{
	BASS_ChannelStop(music->data);
	check_errors();
	BASS_ChannelSetPosition(music->data, 0, BASS_POS_BYTE);
	check_errors();
}

MusicStatus Music_get_status(Music* music)
{
	return (MusicStatus)(BASS_ChannelIsActive(music->data));
}

float Music_get_progress(Music* music)
{
	const float curr = BASS_ChannelGetPosition(music->data, BASS_POS_BYTE);
	check_errors();
	const float length = BASS_ChannelGetLength(music->data, BASS_POS_BYTE);
	check_errors();
	return curr / length;
}

int Music_get_position(Music* music)
{
	//return duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

void Music_update(Music* music)
{
	float current_volume;
	BASS_ChannelGetAttribute(music->data, BASS_ATTRIB_VOL, &current_volume);
	check_errors();

	if (current_volume != volume)
	{
		BASS_ChannelSetAttribute(music->data, BASS_ATTRIB_VOL, volume);
		check_errors();
	}

	//bool current_playing = BASS_ChannelIsActive(music);
}

void Music_check_errors()
{
	// TODO: BASS error codes
	if (BASS_ErrorGetCode() != BASS_OK)
		throw runtime_error(BASS_ErrorGetCode());
}