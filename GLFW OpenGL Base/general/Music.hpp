#pragma once
#include "../Common.hpp"

using namespace std::chrono;

enum MusicStatus
{
	Stopped = 0,
	Playing = 1,
	Paused = 2,
	Stalled = 3
};

class Music
{
public:
	Music(string name);
	~Music();

	void play();
	void pause() const;
	void stop() const;
	MusicStatus get_status() const;
	float get_progress() const;
	int get_position() const;
	string get_name() const;
	void update() const;

	// public for imgui binding
	float volume = 1.0f;

private:
	string name;
	HMUSIC data;
	high_resolution_clock::time_point start_time;

	void check_errors() const;
};