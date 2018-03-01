#include "Backend.hpp"
#include "../Game.hpp"
#include "../general/SharedData.hpp"
#include "../general/Settings.hpp"

void Threads::backend()
{
	{
		unique_lock<mutex> lock(shared.initialized_mutex);
		shared.initialized_cond.wait(lock, [] {return shared.initialized; });
	}

	while (!shared.shutdown)
	{
		game->set_volume(settings.music_volume);

		shared.game_state->update();
	}
}
