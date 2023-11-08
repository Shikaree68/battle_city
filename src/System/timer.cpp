#include "timer.h"

Timer::Timer() 
: is_active_(false)
, time_left_(0){}

void Timer::Update(const double delta) {
	if(is_active_) {
		time_left_ -= delta;
		if(time_left_ <= 0) {
			is_active_ = false;
			callback_();
		}
	}
}

void Timer::Start(const double duration) {
	time_left_ = duration;
	is_active_ = true;
}

void Timer::SetCallback(std::function<void()> callback) {
	callback_ = callback;
}
