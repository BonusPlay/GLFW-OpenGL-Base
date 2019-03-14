#pragma once
#include "../Common.hpp"
#include "../game_objects/Camera.hpp"
#include "../game_objects/Shader.hpp"

class GameState
{
public:
	GameState();
	virtual ~GameState() = default;
<<<<<<< HEAD
=======
	GameState(const GameState&) = default;
	GameState(GameState&&) = default;
	GameState& operator=(const GameState&) = default;
	GameState& operator=(GameState&&) = default;
>>>>>>> a4a49d8... fafa

	virtual void update();
	virtual void update(int key, int scancode, int action, int mods);
	void update(float x_offset, float y_offset) const;
	virtual void render();

protected:
	GLFWwindow* window;
<<<<<<< HEAD
	shared_ptr<Camera> cam;
	shared_ptr<Shader> shader;
=======
	unique_ptr<Camera> cam;
	unique_ptr<Shader> shader;
>>>>>>> a4a49d8... fafa

	virtual void load() = 0;
	void render_fps() const;
	void render_debug_overlay() const;
	void render_gamestate_menu() const;

	glm::mat4 projection;
	atomic<float> delta_time = 0.0f;
	atomic<float> last_frame = 0.0f;
};
