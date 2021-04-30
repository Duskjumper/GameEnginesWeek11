#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {}

Timer::~Timer() {}

void Timer::Start() {
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const {
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}
unsigned int Timer::GetSleepTime(const unsigned int fps_)const {
	unsigned int milliSecPerFrame = MILLI_TO_SEC / fps_;
	if (milliSecPerFrame == 0) {
		return 0;
	}
	unsigned int sleepTime = milliSecPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecPerFrame) {
		return milliSecPerFrame;
	}
	return sleepTime;
}

float Timer::GetCurrentTickMilli() const {
	return static_cast<float>(currentTicks);
}
float Timer::GetCurrentTickSec() const {
	return currentTicks / MILLI_TO_SEC;
}