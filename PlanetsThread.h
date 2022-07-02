#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>

#include "PlanetsController.h"

class PlanetsThread : protected PlanetsController {
	enum modes {
		playing,
		stopped,
		skip_until,
		skip_for,
	};
	std::atomic<modes> mode = stopped; // mode what currently work
	std::atomic<number> speed_multiplier; // speed of playing

	std::atomic<size_t> frequency = 60; // updates peer second

	std::atomic<number> play_until;

	std::atomic<number> play_for;

	std::atomic<bool> stop_token =  true;
	std::atomic<bool> slowdownwarning = false;
	std::atomic<size_t> progress;

	std::atomic<size_t> simulationfrequency;

	std::thread thread;
	mutable std::mutex main_mutex;

public:

	using duration = PlanetsController::duration;

	PlanetsThread(PlanetsController &&source):
		PlanetsController(std::move(source)),
		thread(&PlanetsThread::Thread, this)
	{
	};
	~PlanetsThread(){
		stop_token = false;
		thread.join();
	};

	void Stop() {
		mode = stopped;
	};
	void Play(number speed_mult) {
		speed_multiplier = speed_mult;
		mode = playing;
	}
	void PlayUntil(number time) {
		play_until = time;
		mode = skip_until;
	}
	void PlayFor(number time) {
		play_for = time;
		mode = skip_for;
	};
	bool IsLoading() {
		return mode.load() == skip_until || mode.load() == skip_for;
	}
	bool SlowDownWarning() {
		return slowdownwarning.load();
	}
	size_t GetSimulationFrequency() {
		return simulationfrequency.load();
	}

	size_t GetProgress() {
		return progress.load();
	}
    
	std::string GetTimeDump() {
		std::lock_guard guard(main_mutex);
		return PlanetsController::GetTimeDump();
	}

	std::vector<Planet> LoadState() const {
		std::lock_guard guard(main_mutex);
		std::vector<Planet> planets;
		for (size_t i = 0; i < count; i++)
			planets.push_back(this->operator[](i));
		return planets;
	};

    void SetFrameTime(duration frame_time)
    {
		std::lock_guard guard(main_mutex);
		time_peer_frame = frame_time;
	}

	size_t Count() const { return count; };

private:
	void Thread() {
		while (stop_token) {
			if (mode == playing)
			{	
				using std::chrono::high_resolution_clock;
				auto btime = high_resolution_clock::now();
				{
					std::lock_guard guard(main_mutex);
					PlanetsController::Play(std::chrono::duration<number>(speed_multiplier.load() / frequency.load()));
				}
				auto delta = std::chrono::duration_cast<std::chrono::duration<number>>(high_resolution_clock::now() - btime);
				auto time_to_wait = (1.0 / frequency - delta.count());
				slowdownwarning = time_to_wait <= 0;
				if (slowdownwarning)
					time_to_wait = 0;
				simulationfrequency = (speed_multiplier.load() / frequency.load()) / (time_to_wait + delta.count());
				std::this_thread::sleep_for(std::chrono::duration<number>(time_to_wait));
			}
			else if (mode == stopped) {
				std::this_thread::yield();
			}
			else if (mode == skip_until) {
				std::lock_guard guard(main_mutex);
				for (size_t i = 0; i < 100; i++) {
					PlanetsController::Play((std::chrono::duration<number>(play_until.load()) - this->time) / 100);
					progress = i;
				}
				mode = stopped;
			}
			else if (mode == skip_for) {
				std::lock_guard guard(main_mutex);
				for (size_t i = 0; i < 100; i++) {
					PlanetsController::Play(std::chrono::duration<number>(play_for.load()) / 100);
					progress = i;
				}
				mode = stopped;
			}

		}
	}
};