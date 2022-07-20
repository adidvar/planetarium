#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>

#include "PlanetsController.h"

class PlanetsThread : protected PlanetsController {

	struct spinlock {
		std::atomic<bool> lock_ = { false };

		void lock() { while (lock_.exchange(true, std::memory_order_acquire)); }

		bool try_lock() 
		{
			return !lock_.exchange(true, std::memory_order_acquire);
		}

		void unlock() { lock_.store(false, std::memory_order_release); }
	};

	enum modes {
		playing,
		stopped,
		skip_until,
		skip_for,
	};
	const static size_t frequency = 60; // executin frequency
	
	std::atomic<modes> mode = stopped; // mode what currently work
	std::atomic<number> speed_multiplier; // speed of playing
	std::atomic<number> play_until;
	std::atomic<number> play_for;

	std::atomic<bool> slowdownwarning = false;
	std::atomic<size_t> progress;

	std::atomic<size_t> simulationfrequency;

	std::thread thread;
	std::atomic<bool> stop_token =  true;

	mutable spinlock main_mutex;

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
		mode.store(stopped , std::memory_order_relaxed);
	};
	void Play(number speed_mult) {
		speed_multiplier.store(speed_mult, std::memory_order_relaxed);
		mode.store(playing, std::memory_order_release);
	}
	void PlayUntil(number time) {
		play_until.store(time, std::memory_order_relaxed);
		mode.store(skip_until, std::memory_order_release);
	}
	void PlayFor(number time) {
		play_for.store(time, std::memory_order_relaxed);
		mode.store(skip_for, std::memory_order_release);
	};
	bool IsLoading() const {
		return mode.load(std::memory_order_relaxed) == skip_until || mode.load(std::memory_order_relaxed) == skip_for;
	}

	size_t GetProgress() const {
		return progress.load(std::memory_order_relaxed);
	}

	bool SlowDownWarning() const {
		return slowdownwarning.load(std::memory_order_relaxed);
	}
    
	std::string GetTimeDump() const {
		std::lock_guard guard(main_mutex);

	size_t second = time.count();
	size_t minutes = second / 60;
	size_t hours = minutes / 60;
	size_t days = hours / 24;
	size_t years = days / 365;

	second %= 60;
	minutes %= 60;
	hours %= 24;
	days %= 365;

	std::stringstream ss;
	ss << "Y:" << years << std::endl
		<< "D:" << days << std::endl
		<< "H:" << hours << std::endl
		<< "M:" << minutes << std::endl
		<< "S:" << second << std::endl;
	return ss.str();
	}

	void SetPrecision(duration dtime) {
		std::lock_guard guard(main_mutex);
		PlanetsController::SetPrecision(dtime);
	}
	size_t GetSpeed() const
	{
		std::lock_guard guard(main_mutex);
		return speed_multiplier.load(std::memory_order_relaxed);
	}

	std::vector<Planet> LoadState() const {
		std::lock_guard guard(main_mutex);
		std::vector<Planet> planets;
		for (size_t i = 0; i < count; i++)
			planets.push_back(this->operator[](i));
		return planets;
	};

	size_t Count() const { return count; };
private:
	void Thread() {
		while (stop_token) {
			auto cmode = this->mode.load(std::memory_order_relaxed);
			if (cmode == playing)
			{	
				using std::chrono::high_resolution_clock;
				auto btime = high_resolution_clock::now();
				{
					std::lock_guard guard(main_mutex);
					auto delta = std::chrono::duration_cast<duration>(high_resolution_clock::now() - btime);
					PlanetsController::Play(duration(speed_multiplier.load() / frequency)+delta*speed_multiplier.load());
				}
				auto delta = std::chrono::duration_cast<duration>(high_resolution_clock::now() - btime);
				auto time_to_wait = (1.0 / frequency - delta.count());
				slowdownwarning = time_to_wait <= 0;
				if (slowdownwarning)
					time_to_wait = 0;
				simulationfrequency = (speed_multiplier.load() / frequency) / (time_to_wait + delta.count());
				std::this_thread::sleep_for(duration(time_to_wait));
			}
			else if (cmode == stopped) {
				std::this_thread::yield();
			}
			else if (cmode == skip_until) {
				std::lock_guard guard(main_mutex);
				auto part_duration = (duration(play_until.load()) - this->time) / 100;
				for (size_t i = 0; i < 100; i++) {
					PlanetsController::Play(part_duration);
					progress = i;
				}
				mode = stopped;
			}
			else if (cmode == skip_for) {
				std::lock_guard guard(main_mutex);
				auto part_duration = duration(play_for.load()) / 100;
				for (size_t i = 0; i < 100; i++) {
					PlanetsController::Play(part_duration);
					progress = i;
				}
				mode = stopped;
			}

		}
	}
};