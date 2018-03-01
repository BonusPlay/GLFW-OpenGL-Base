#pragma once
#include "../Common.hpp"
#include "GameState.hpp"
#include "../general/Model.hpp"
#include "../general/CubeMap.hpp"
#include "../general/Music.hpp"

class ExampleState : public GameState
{
public:
	ExampleState ();
	~ExampleState () = default;

	void render () override;
	void update () override;
	void update (int key, int scancode, int action, int mods) override;

private:
	shared_ptr<Music> music;
	shared_ptr<Model> model;
	shared_ptr<Shader> shader_skybox;
	shared_ptr<CubeMap> skybox;

	void load () override;
	void render_music_menu () const;
};
