#pragma once
#include "util.h"

class Ray {
public:
	Ray() :origin(Point3f(0, 0, 0)), direction(Vector3f(1, 0, 0)) {}
	Ray(const Point3f& origin, const Vector3f direction) :origin(origin), direction(direction.norm() > 0 ? direction.normalized() : Vector3f(1, 0, 0)) {}

	const Point3f& orig() const { return origin; }
	void orig(Point3f p) { origin = p; }

	const Vector3f& dir() const { return direction; }
	void dir(Vector3f d) { direction = d; }

	Point3f at(float t) const { return origin + t * direction; }

	// Input normal must be normalized
	Vector3f reflect(const Vector3f& normal) const;

	Vector3f refract(const Vector3f& normal, float etai_over_etat) const ;

private:
	Point3f origin;
	Vector3f direction;
};
