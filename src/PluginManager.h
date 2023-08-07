#pragma once

#include <filesystem>
#include <iostream>

#include <boost/dll.hpp>

#include "FileFormat.h"

/**
 * Plugin loading class
 */
class PluginManager {
	std::vector<FileFormat*> ff_plugins;
	std::vector<boost::dll::shared_library> plugins;
public:
	PluginManager();
	/**
	 * Return supported file formats
	 * 
	 * \return formats
	 */
	const std::vector<FileFormat*>& formats();
};