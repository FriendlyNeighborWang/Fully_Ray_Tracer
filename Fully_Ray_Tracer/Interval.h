#pragma once
#include "util.h"

class Interval {
public:
	float min, max;
	static const Interval empty, universe;

	Interval():min(+INF),max(-INF){}
	Interval(float min, float max):min(min),max(max){}
	float  size() const {
		return max - min;
	}
	bool contains(float x) const {
		return min <= x && x <= max;
	}
	// No Boundaries
	bool surrounds(double x) const {
		return min < x && x < max;
	}
	double clamp(double x) const {
		if (x < min)return min;
		if (x > max)return max;
		return x;
	}
};