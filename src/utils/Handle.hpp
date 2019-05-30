#pragma once

/**
 * \brief Helper class for objects that have native handle
 * \details Since they cannot be copied (since dctor would clean data on GPU)
 * \details this class removes copy operations.
 * \details For move operations it adds a bool field to check on dctor if it
 * \details should remove objects.
 */
class Handle
{
public:
	Handle() noexcept = default;
	Handle(const Handle&) = delete;
	Handle(Handle&& other) noexcept
	{
		other.moved = true;
	}
	Handle& operator=(const Handle&) = delete;
	Handle& operator=(Handle&& other) noexcept
	{
		other.moved = true;
		return *this;
	}
	~Handle() noexcept = default;

protected:
	bool moved = false;
};