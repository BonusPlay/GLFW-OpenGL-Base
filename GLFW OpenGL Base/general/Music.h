#pragma once
#include <bass.h>

typedef enum
{
	Stopped = 0,
	Playing = 1,
	Paused  = 2,
	Stalled = 3
} MusicStatus;

typedef struct
{
	char* name;
	HMUSIC data;
	// TODO: music time
	// high_resolution_clock::time_point start_time;
	float volume;
} Music;

Music* Music_Ctor(char* name);
void Music_DCtor(Music* m);

void Music_Play(Music* m);
void Music_Pause(Music* m);
void Music_Stop(Music* m);
MusicStatus Music_GetStatus(Music* m);
float Music_GetProgress(Music* m);
int Music_GetPosition(Music* m);
void Music_Update(Music* m);