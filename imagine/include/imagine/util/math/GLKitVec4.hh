#pragma once

/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <GLKit/GLKMathTypes.h>
#include <GLKit/GLKVector4.h>

class GLKitVec4
{
public:
	GLKVector4 v{{0}};

	constexpr GLKitVec4() {}
	constexpr GLKitVec4(float x, float y, float z, float w): v{{x, y, z, w}} {}
	constexpr GLKitVec4(const GLKVector4 &v): v{{v.x, v.y, v.z, v.w}} {}
};
