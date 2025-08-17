#pragma once

#include <cstdint>

class GameState {
public:
	virtual void Render() const = 0;
	virtual void Update(double delta) = 0;
	virtual ~GameState() = default;
	virtual std::uint32_t GetStateWidth() const = 0;
	virtual std::uint32_t GetStateHeight() const = 0;
};

