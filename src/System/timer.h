#pragma once

#include <functional>


class Timer {
public:
	Timer();
	void Update(const double delta);
	void Start(const double duration);
	void SetCallback(std::function<void()> callback);

private:
	std::function<void()> callback_;
	double time_left_;
	bool is_active_;
};