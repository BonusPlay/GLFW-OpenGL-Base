#pragma once
#include "../Common.hpp"
#include "GameState.hpp"
#include "../game_objects/Model.hpp"
#include "../game_objects/CubeMap.hpp"
#include "../game_objects/Music.hpp"

class ExampleState : public GameState
{
public:
	ExampleState();
	~ExampleState() override = default;

	void render() override;
	void update() override;
	void update(int key, int scancode, int action, int mods) override;

private:
	unique_ptr<Music> music;
	unique_ptr<Model> model;
	unique_ptr<Shader> shader_skybox;
	unique_ptr<CubeMap> skybox;

	void load() override;
	void render_music_menu() const;
};
