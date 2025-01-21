#pragma once
#include "Object.h"
#include "Material.h"

class Sphere : public Object {
public:
	Sphere(const Point3f& c, float r, std::shared_ptr<Material> m) :Object(std::move(AABB(c - Vector3f(r,r,r), c + Vector3f(r,r,r)))), center(c), radius(r), mat(std::move(m)) {}

	virtual bool intersect(const Ray& r, Interval bound, Inter_record& rec) const;

private:
	Point3f center;
	float radius;
	std::shared_ptr<Material> mat;
};

