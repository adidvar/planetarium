#pragma once
/*****************************************************************//**
 * \file   PositionTransformer.h
 * \brief Class to coodinates transformation
 * 
 * 
 * \author adidvar 
 * \date July 2022
 *********************************************************************/
#include <algorithm>

#include "Number.h"
#include "Vector.h"

//! transforms coodinates
class PTransformer {
    //! screen sizes
    size_t width, height;

	//! screen left top and right bottom positions
	Vector cposition[2] = {{-(number)width, -(number)height },{(number)width,(number)height}};

	static number transform_p(number current_position, number max_position, number proect_max_pos);
public:
	/**
	 * \param width screen width
	 * \param height screen height
	 */
	PTransformer(size_t width, size_t height);
	/**
	 * Get screen x coordinate from real one
	 * 
	 * \param current_position coordinate
	 * \return  screen coordinate
	 */
	number ScaleW(number current_position) const;
	/**
	 * Get screen x coordinate from real one
	 *
	 * \param current_position coordinate
	 * \return   screen coordinate
	 */
	number ScaleH(number current_position) const;
	/**
	 * Scale absolute value into screen coordinates
	 * 
	 * \param current_position coordinate
	 * \return screen coordinate
	 */
	number Scale(number current_position) const;
	/**
	 * Move camera
	 * 
	 * \param x x delta
	 * \param y y delta
	 */
	void MoveCameraP(number x, number y);
	/**
	 * Scale on multiplier 
	 * 
	 * \param factor multiplier
	 */
	void ScaleCamera(number factor);
	/**
	 * Set camera scale
	 * 
	 * \param dwidth x scale
	 * \param dheight y scale
	 */
	void SetScale(number dwidth, number dheight);
};
