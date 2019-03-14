#include "Music.hpp"

Music::Music(string name)
<<<<<<< HEAD
{
	this->name = name;
=======
	: name(std::move(name))
{
>>>>>>> a4a49d8... fafa
	music = BASS_StreamCreateFile(false, ("res/music/" + name + ".mp3").c_str(), 0, 0, 0);
	check_errors();
}

Music::~Music()
{
	BASS_StreamFree(music);
	check_errors();
}

void Music::play()
{
	BASS_ChannelPlay(music, false);
	check_errors();
	start_time = high_resolution_clock::now();
}

// TODO: handle clock on pauses
void Music::pause() const
{
	BASS_ChannelPause(music);
	check_errors();
}

void Music::stop() const
{
	BASS_ChannelStop(music);
	check_errors();
	BASS_ChannelSetPosition(music, 0, BASS_POS_BYTE);
	check_errors();
}

MusicStatus Music::get_status() const
{
	return static_cast<MusicStatus>(BASS_ChannelIsActive(music));
}

float Music::get_progress() const
{
	const float curr = BASS_ChannelGetPosition(music, BASS_POS_BYTE);
	check_errors();
	const float length = BASS_ChannelGetLength(music, BASS_POS_BYTE);
	check_errors();
	return curr / length;
}

int Music::get_position() const
{
	return duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

string Music::get_name() const
{
	return name;
}

void Music::update() const
{
	float current_volume;
	BASS_ChannelGetAttribute(music, BASS_ATTRIB_VOL, &current_volume);
	check_errors();

	if (current_volume != volume)
	{
		BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, volume);
		check_errors();
	}

	bool current_playing;
	BASS_ChannelIsActive(music);
}

void Music::check_errors() const
{
	if (BASS_ErrorGetCode() != BASS_OK)
		throw runtime_error(std::to_string(BASS_ErrorGetCode()));
}
