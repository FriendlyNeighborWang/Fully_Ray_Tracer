#pragma once
#include "Ray.h"
#include "Interval.h"
#include "Inter_record.h"
#include "AABB.h"

class Object {
public:
	Object(){}
	Object(AABB aabb):aabb(aabb){}
	virtual bool intersect(const Ray& r, Interval bound, Inter_record& rec) const = 0;
public:
	AABB aabb;
};