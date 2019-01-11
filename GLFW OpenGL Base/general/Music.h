#pragma once

typedef enum
{
	Stopped = 0,
	Playing = 1,
	Paused  = 2,
	Stalled = 3
} MusicStatus;

// TODO: dummy type
typedef HMUSIC;

typedef struct
{
	char* name;
	HMUSIC data;
	// TODO: time
	// high_resolution_clock::time_point start_time;
	float volume;
} Music;

Music* Music_Ctor(char* name);
void Music_DCtor(Music* music);

void Music_play(Music* music);
void Music_pause(Music* music);
void Music_stop(Music* music);
MusicStatus Music_get_status(Music* music);
float Music_get_progress(Music* music);
int Music_get_position(Music* music);
void Music_update(Music* music);