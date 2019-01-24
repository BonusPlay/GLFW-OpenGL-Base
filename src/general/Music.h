#pragma once
#include <bass.h>

/**
 * @brief Enum with music states
 */
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
	float volume;
} Music;

/**
 * Music constructor
 * @param name Song name (has to have corresponding file in resources)
 * @returns music
 */
Music* Music_Ctor(char* name);

/**
 * @brief Music deconstructor
 * @param m Music to deconstruct
 */
void Music_DCtor(Music* m);

/**
 * @brief Plays music
 * @param m Music to play
 */
void Music_Play(Music* m);

/**
 * @brief Pauses music
 * @param m Music to pause
 */
void Music_Pause(Music* m);

/**
 * @brief Stops music
 * @param m Music to stop
 */
void Music_Stop(Music* m);

/**
 * @brief Returns current music status
 * @param m Music to return status for
 * @returns Music status
 */
MusicStatus Music_GetStatus(Music* m);

/**
 * @brief Returns music progress in percentage (0.00 - 1.00)
 * @param m Music to return progress for
 * @returns Music progress
 */
float Music_GetProgress(Music* m);

/**
 * @brief Update music volume based on global setting
 * @param m Music to update
 */
void Music_Update(Music* m);