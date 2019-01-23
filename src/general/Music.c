/** @file */
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
	if (!music)
		panic("malloc failed in Music_Ctor");

	char* path = concat3("res/music/", name, ".mp3");
	music->data = BASS_StreamCreateFile(false, path, 0, 0, 0);
	free(path);
	music->name = name;
	music->volume = 1.0f;

	return music;
}

void Music_DCtor(Music* m)
{
	assert(m);
	LogD("Music_DCtor");

	BASS_StreamFree(m->data);
	free(m);
}

void Music_Play(Music* m)
{
	assert(m);
	LogD("Music_Play on %s", m->name);

	BASS_ChannelPlay(m->data, false);
	check_errors();
	//start_time = high_resolution_clock::now();
}

void Music_Pause(Music* m)
{
	assert(m);
	LogD("Music_Pause on %s", m->name);

	BASS_ChannelPause(m->data);
	check_errors();
}

void Music_Stop(Music* m)
{
	assert(m);
	LogD("Music_Stop on %s", m->name);

	BASS_ChannelStop(m->data);
	check_errors();
	BASS_ChannelSetPosition(m->data, 0, BASS_POS_BYTE);
	check_errors();
}

MusicStatus Music_GetStatus(Music* m)
{
	assert(m);
	return (MusicStatus)BASS_ChannelIsActive(m->data);
}

float Music_GetProgress(Music* music)
{
	assert(music);
	const float current = BASS_ChannelGetPosition(music->data, BASS_POS_BYTE);
	check_errors();
	const float length = BASS_ChannelGetLength(music->data, BASS_POS_BYTE);
	check_errors();
	return current / length;
}

void Music_Update(Music* m)
{
	assert(m);
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