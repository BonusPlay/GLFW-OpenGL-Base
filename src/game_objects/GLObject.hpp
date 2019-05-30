#pragma once

/**
 * \brief Helper class for OpenGL objects
 * \details Since they cannot be copied (since dctor would clean data on GPU)
 * \details this class removes copy operations.
 * \details For move operations it adds a bool field to check on dctor if it
 * \details should remove objects.
 */
class GLObject
{
public:
	GLObject() noexcept = default;
	
	GLObject(const GLObject&) = delete;

	GLObject(GLObject&& other) noexcept
	{
		other.moved = true;WS
	}

	GLObject& operator=(const GLObject&) = delete;

	GLObject& operator=(GLObject&& other) noexcept
	{
		other.moved = true;
		return *this;
	}

	~GLObject() noexcept = default;

protected:
	bool moved = false;
};