#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

#include "PlanetsController.h"

template <typename number>
class PlanetsThread : protected PlanetsController<number> {
	enum modes {
		playing,
		stopped,
		skip_until,
		skip_for,
	};
	std::atomic<modes> mode; // mode what currently work

	std::atomic<number> speed_multiplier; // speed of playing

	std::atomic<size_t> frequency; // updates peer second

	std::atomic<number> play_until;

	std::atomic<number> play_for;

	std::atomic<bool> stop_token =  true;
	std::atomic<bool> slowdownwarning = false;
	std::atomic<size_t> progress;

	std::atomic<size_t> simulationfrequency;

	std::thread thread;
	mutable std::mutex main_mutex;

public:

    using number_t = number;

	PlanetsThread(size_t count) :
		PlanetsController(count),
		thread(&PlanetsThread::Thread, this),
		mode(stopped)
	{
		thread.detach();
	};

	void Stop() {
		mode = stopped;
	};
	void Play(number speed_mult, size_t frequency) {
		speed_multiplier = speed_mult;
		this->frequency = frequency;
		mode = playing;
	}
	void PlayUntil(number time) {
		play_until = time;
		moode = skip_until;
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
		return PlanetsController::GetTimeDump();
	}

	Planet<number> operator [](size_t i) const {
		return Planet<number>(name[i], mass[i], density[i], x[i], y[i], speed_x[i], speed_y[i], accel_x[i], accel_y[i]);
	}

    void SetTaktTime(std::chrono::duration<number> dtime)
    {
		std::lock_guard guard(main_mutex);
		time_peer_takt = dtime;
	}

	size_t Count() const { return count; };

	void ConnectHandle(size_t planet_index, std::shared_ptr<PlanetHandle<number>> handle)  {
		std::lock_guard guard(main_mutex);
		PlanetsController<number>::ConnectHandle(planet_index, handle);
	}
private:
	void Thread() {
		while (stop_token) {
			if (mode == playing)
			{	
				using std::chrono::high_resolution_clock;
				auto btime = high_resolution_clock::now();
				{
					std::lock_guard guard(main_mutex);
					Calculate(std::chrono::duration<number>(speed_multiplier.load() / frequency.load()));
					PlanetsController<number>::ExecuteHandles(std::chrono::duration<number>(speed_multiplier.load() / frequency.load()));
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
					Calculate((std::chrono::duration<number>(play_until.load()) - this->time) / 100);
					progress = i;
				}
				mode = stopped;
			}
			else if (mode == skip_for) {
				std::lock_guard guard(main_mutex);
				for (size_t i = 0; i < 100; i++) {
					Calculate(std::chrono::duration<number>(play_for.load()) / 100);
					progress = i;
				}
				mode = stopped;
			}

		}
	}
public:
    [[deprecated]]
    static std::unique_ptr<PlanetsThread<number>> FromFile(std::string filename) {
        std::ifstream file;
        file.open(filename.c_str());

        size_t count;
        file >> count;
        auto planets = new PlanetsThread<number>(count);
        std::string delta_time, orbit_len, vector_scale, default_scale;
        file >> delta_time >> orbit_len >>vector_scale >> default_scale;

        for (size_t i = 0; i < count; i++) {
            if (!file)std::exit(1);
            file >> planets->name[i] >> planets->mass[i] >> planets->density[i] >> planets->x[i] >> planets->y[i] >> planets->speed_x[i] >> planets->speed_y[i];
        }

        file.close();
        return std::unique_ptr<PlanetsThread<number>>(planets);
    }
};