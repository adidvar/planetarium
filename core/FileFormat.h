#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include "PlanetsController.h"

class FileFormatSyntaxError : public std::exception {
};
class FileFormatUnsupportedFormat : public std::exception {
};

class FileFormat {
public:
	virtual ~FileFormat(){};
	virtual std::vector<std::string> Formats() = 0;
	virtual PlanetsController Load(const std::string & file_name) = 0;
	virtual void Save(const PlanetsController & , const std::string & file_name) = 0;
};