#include "PluginManager.h"

PluginManager::PluginManager() {
	for (auto&& path : std::filesystem::recursive_directory_iterator(".")) {
		if (!path.is_regular_file())
			continue;
		if (path.path().extension() != ".dll")
			continue;
		// Class `library_info` can extract information from a library
		boost::dll::library_info inf(path.path().string());

		// Getting symbols exported from 'Anna' section
		std::vector<std::string> exports = inf.symbols("ff");

		if (exports.size() == 0)
			continue;
		// Loading library and importing symbols from it
		boost::dll::shared_library lib(path.path().string());
		for (auto s_name : exports) {
			std::cout << "Loaded " << s_name << " from " << path.path().string() << " ";
			ff_plugins.push_back(lib.get<FileFormat*>(s_name));
			auto format = ff_plugins.back()->Formats();
			std::copy(format.begin(), format.end(), std::ostream_iterator<std::string>(std::cout, " "));
		}
		plugins.push_back(lib);
	}
}

const std::vector<FileFormat*>& PluginManager::formats()
{
	return ff_plugins;
};


