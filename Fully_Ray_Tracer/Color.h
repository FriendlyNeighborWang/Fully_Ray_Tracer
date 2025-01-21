#pragma once
#include "util.h"
#include "Interval.h"
#include <opencv2/opencv.hpp>

using Color = Vector3f;

inline Color operator*(const Color& color1, const Color& color2) {
	return Color(color1[0] * color2[0], color1[1] * color2[1], color1[2] * color2[2]);
}