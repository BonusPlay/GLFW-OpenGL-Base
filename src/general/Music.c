#include "Music.h"
#include <stdbool.h>
#include "../utils/SwissArmyKnife.h"
#include "../utils/Typedefs.h"

void check_errors();


/*********************************************
****************    public    ****************
*********************************************/

Music* Music_Ctor(char* name)
{
	LogD("Music_Ctor\n");
	Music* music = (Music*)malloc(sizeof(Music));

	music->data = BASS_StreamCreateFile(false, concat3("res/music/", name, ".mp3"), 0, 0, 0);
	music->name = name;
	music->volume = 1.0f;

	return music;
}

void Music_DCtor(Music* m)
{
	BASS_StreamFree(m->data);
	free(m);
}

void Music_Play(Music* m)
{
	BASS_ChannelPlay(m->data, false);
	check_errors();
	//start_time = high_resolution_clock::now();
}

void Music_Pause(Music* m)
{
	BASS_ChannelPause(m->data);
	check_errors();
}

void Music_Stop(Music* m)
{
	BASS_ChannelStop(m->data);
	check_errors();
	BASS_ChannelSetPosition(m->data, 0, BASS_POS_BYTE);
	check_errors();
}

MusicStatus Music_GetStatus(Music* m)
{
	return (MusicStatus)BASS_ChannelIsActive(m->data);
}

float Music_GetProgress(Music* music)
{
	const float current = BASS_ChannelGetPosition(music->data, BASS_POS_BYTE);
	check_errors();
	const float length = BASS_ChannelGetLength(music->data, BASS_POS_BYTE);
	check_errors();
	return current / length;
}

int Music_GetPosition(Music* music)
{
	// TODO: not implemented
	return 0;
	//return duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

void Music_Update(Music* m)
{
	float current_volume;
	BASS_ChannelGetAttribute(m->data, BASS_ATTRIB_VOL, &current_volume);
	check_errors();

	if (current_volume != m->volume)
	{
		BASS_ChannelSetAttribute(m->data, BASS_ATTRIB_VOL, m->volume);
		check_errors();
	}

	//bool current_playing = BASS_ChannelIsActive(music);
}


/**********************************************
****************    private    ****************
**********************************************/

void check_errors()
{
	// TODO: BASS error codes
	if (BASS_ErrorGetCode() != BASS_OK);
		//throw runtime_error(BASS_ErrorGetCode());
		// TODO: error handling
}