#pragma once

#include <cstdint>
#include <array>

class GameState {
public:
	virtual void Render() const = 0;
	virtual void Update(double delta) = 0;
	virtual ~GameState() = default;
	virtual void ProcessInput(const std::array<bool, 349> &keys) = 0;
	virtual std::uint32_t GetStateWidth() const = 0;
	virtual std::uint32_t GetStateHeight() const = 0;
};

