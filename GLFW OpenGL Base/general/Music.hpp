#pragma once
#include "../Common.hpp"

using namespace std::chrono;

class Music
{
public:
	Music (string name);
	~Music () = default;
	void play ();
	float get_progress () const;
	int get_position () const;
	string get_name () const;

private:
	string name;
	HMUSIC music;
	high_resolution_clock::time_point start_time;

	void check_errors () const;
};