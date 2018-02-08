#include "Music.hpp"

Music::Music (string name)
{
	this->name = name;
	music = BASS_StreamCreateFile (false, ("res/music/" + name + ".mp3").c_str (), 0, 0, 0);
	check_errors ();
}

void Music::play ()
{
	BASS_ChannelPlay (music, false);
	check_errors ();
	start_time = high_resolution_clock::now ();
}

float Music::get_progress () const
{
	const float curr = BASS_ChannelGetPosition (music, BASS_POS_BYTE);
	check_errors ();
	const float length = BASS_ChannelGetLength (music, BASS_POS_BYTE);
	check_errors ();
	return curr / length;
}

int Music::get_position () const
{
	return duration_cast<milliseconds>(std::chrono::high_resolution_clock::now () - start_time).count ();
}

string Music::get_name() const
{
	return name;
}

void Music::check_errors () const
{
	if (BASS_ErrorGetCode () != BASS_OK)
		throw runtime_error (std::to_string (BASS_ErrorGetCode ()));
}
