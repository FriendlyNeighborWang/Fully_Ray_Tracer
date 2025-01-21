#include"Sphere.h"

bool Sphere::intersect(const Ray& r, Interval bound, Inter_record& rec) const {
	if (!aabb.intersect(r, bound))
		return false;
	
	Vector3f oc = center - r.orig();
	auto a = r.dir().squaredNorm();
	auto h = r.dir().dot(oc);
	auto c = oc.squaredNorm() - radius * radius;
	auto discriminant = h * h - a * c;

	if (discriminant < 0)
		return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (h - sqrtd) / a;
	if (!bound.surrounds(root)) {
		root = (h + sqrtd) / a;
		if (!bound.surrounds(root))
			return false;
	}

	rec.t = root;
	rec.p = r.at(root);
	Vector3f outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat = mat;

	return true;
}