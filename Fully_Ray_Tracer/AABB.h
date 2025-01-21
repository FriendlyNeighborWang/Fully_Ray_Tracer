#pragma once
#include "util.h"
#include "Ray.h"
#include "Interval.h"

class AABB {
public:
	AABB(){}
	AABB(Vector3f min, Vector3f max) :_min(min), _max(max) {}
	Vector3f min() const { return _min; }
	Vector3f max() const { return _max; }
	Vector3f mid() const { return (_min + _max) * 0.5f; }
	AABB& operator=(const AABB aabb);

	enum axis { X = 0, Y, Z };

	AABB& merge(const AABB& aabb);
	bool intersect(const Ray& r, Interval bound) const;
private:
	inline std::pair<float, float> t_in_out(const Ray& r, axis a) const;

	Vector3f _min;
	Vector3f _max;
};