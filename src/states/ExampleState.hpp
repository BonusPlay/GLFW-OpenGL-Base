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
	~ExampleState() = default;
<<<<<<< HEAD
=======
	ExampleState(const ExampleState&) = default;
	ExampleState(ExampleState&&) = default;
	ExampleState& operator=(const ExampleState&) = default;
	ExampleState& operator=(ExampleState&&) = default;
>>>>>>> a4a49d8... fafa

	void render() override;
	void update() override;
	void update(int key, int scancode, int action, int mods) override;

private:
<<<<<<< HEAD
	shared_ptr<Music> music;
	shared_ptr<Model> model;
	shared_ptr<Shader> shader_skybox;
	shared_ptr<CubeMap> skybox;
=======
	unique_ptr<Music> music;
	unique_ptr<Model> model;
	unique_ptr<Shader> shader_skybox;
	unique_ptr<CubeMap> skybox;
>>>>>>> a4a49d8... fafa

	void load() override;
	void render_music_menu() const;
};
