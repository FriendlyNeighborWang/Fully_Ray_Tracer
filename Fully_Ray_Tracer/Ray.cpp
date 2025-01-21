#include "Ray.h"

Vector3f Ray::reflect(const Vector3f& normal) const {
	return direction - 2 * direction.dot(normal) * normal;
}

Vector3f Ray::refract(const Vector3f& normal, float etai_over_etat) const {
	auto cos_theta = std::min((-direction).dot(normal), 1.0f);
	Vector3f r_out_perp = etai_over_etat * (direction + cos_theta * normal);
	float r_out_parallel_squared = 1.0f - r_out_perp.squaredNorm();

	// Total internal reflection 
	if (r_out_parallel_squared < 0.0f)
		return reflect(normal);

	Vector3f r_out_parallel = -sqrt(r_out_parallel_squared) * normal;
	return r_out_perp + r_out_parallel;
}