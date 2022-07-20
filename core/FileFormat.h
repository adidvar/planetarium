#pragma once
/*****************************************************************//**
 * \file   FileFormat.h
 * \brief  File format module class
 * 
 * \author adidvar 
 * \date   July 2022
 *********************************************************************/

#include <string>
#include <vector>
#include <stdexcept>

#include "PlanetsController.h"

/**
 * File format loading error exception 
 */
class FileFormatSyntaxError : public std::exception {
};
/**
 *	File format class 
 */
class FileFormat {
public:
	virtual ~FileFormat(){};
	/**
	 * \return supported formats
	 */
	virtual std::vector<std::string> Formats() = 0;
	/**
	 * Load system from class 

	 * \param file_name file name
	 * \throw FileFormatSyntaxError when file loading error happen
	 * \return PlanetController class
	 */
	virtual PlanetsController Load(const std::string & file_name) = 0;
	/**
	 * Save system to file
	 * \param[in] system PlanetsController to write
	 * \param file_name file name
	 */
	virtual void Save(const PlanetsController & system , const std::string & file_name) = 0;
};