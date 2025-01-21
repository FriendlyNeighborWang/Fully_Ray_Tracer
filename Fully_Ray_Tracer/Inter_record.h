#pragma once
#include "util.h"
#include "Ray.h"

class Material;

class Inter_record {
public:
	Point3f p;
	Vector3f normal;
	std::shared_ptr<Material> mat;
	float t;
	bool front_face;
	void set_face_normal(const Ray& r, const Vector3f& outward_normal) {
		front_face = r.dir().dot(outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

};