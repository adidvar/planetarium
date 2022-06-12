#pragma once
#include <unordered_map>
#include <type_traits>
#include <string>
#include <stdexcept>
#include <mutex>

class Options {
	std::unordered_map <std::string, std::string> options;
	mutable std::mutex mutex;
public:
	std::string Get(std::string name) const 
	{
		std::lock_guard guard(mutex);
		return options.at(name); 
	};
	void Set(std::string name, std::string value)
	{ 
		std::lock_guard guard(mutex);
		options[name] = value; 
	};
};

template<typename T>
class Option {
	
	const Options& opts; std::string name;
public:
	Option(const Options& opts , std::string name) :
		name(name),
		opts(opts) {};

	T Get() {
		if constexpr (std::is_integral<T>::value)
			return (T)std::stoll(opts.Get(name));
		if constexpr (std::is_floating_point<T>::value)
			return (T)std::stold(opts.Get(name));
		if constexpr (std::is_same<std::string,T>::value)
			return opts.Get(name);
		if constexpr (std::is_same<bool, T>::value) {
			auto&& value = opts.Get(name);
			if (value == "true")
				return true;
			else if (value == "false")
				return false;
			else
				throw std::invalid_argument(std::string("option ") + name + " isn`t a bool value");
		}
	};
};