#include "AABB.h"

AABB& AABB::operator=(const AABB aabb) {
	this->_min = aabb._min;
	this->_max = aabb._max;
	return *this;
}

AABB& AABB::merge(const AABB& aabb) {
	_min.x() = std::min(_min.x(), aabb._min.x());
	_min.y() = std::min(_min.y(), aabb._min.y());
	_min.z() = std::min(_min.z(), aabb._min.z());
	_max.x() = std::max(_max.x(), aabb._max.x());
	_max.y() = std::max(_max.y(), aabb._max.y());
	_max.z() = std::max(_max.z(), aabb._max.z());
	return *this;
}

bool AABB::intersect(const Ray& r, Interval bound) const {
	auto t_x_in_out = t_in_out(r, X);
	auto t_y_in_out = t_in_out(r, Y);
	auto t_z_in_out = t_in_out(r, Z);

	auto t_in = std::max(std::max(bound.min, t_x_in_out.first), std::max(t_y_in_out.first, t_z_in_out.first));

	auto t_out = std::min(std::min(bound.max, t_x_in_out.second), std::min(t_y_in_out.second, t_z_in_out.second));

	return t_in < t_out;
}


inline std::pair<float, float> AABB::t_in_out(const Ray& r, axis a) const {
	auto dir = r.dir()[a];
	auto o = r.orig()[a];

	if (std::fabs(dir) < EPS) {
		if (o<_min[a] || o>_max[a])
			return{ INF,-INF };
		else
			return { -INF, INF };
	}

	auto t1 = (_min[a] - o) / dir;
	auto t2 = (_max[a] - o) / dir;
	auto t_in = std::min(t1, t2);
	auto t_out = std::max(t1, t2);
	return { t_in,t_out };
}