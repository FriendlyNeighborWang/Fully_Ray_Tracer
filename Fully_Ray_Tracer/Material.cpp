#include "Material.h"

bool Lambertian::scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const {
	Vector3f scatter_direction = rec.normal + random_unit_vec();

	if ((scatter_direction.x() < EPS) && (scatter_direction.y() < EPS) &&
		(scatter_direction.z() < EPS))
		scatter_direction = rec.normal;

	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}

bool Metal::scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const {
	Vector3f reflected = r_in.reflect(rec.normal.normalized()).normalized();
	reflected = reflected + (fuzz * random_unit_vec());

	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return (scattered.dir().dot(rec.normal) > 0);
}

bool Dielectric::scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const {
	attenuation = Color(1.0f, 1.0f, 1.0f);
	float ri = rec.front_face ? (1.0f / refraction_index) : refraction_index;

	Vector3f unit_direction = r_in.dir().normalized();
	float cos_theta = std::min((-unit_direction).dot(rec.normal), 1.0f);
	float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	// Refraction or Total internal reflection 
	bool if_refract = ri * sin_theta < 1.0f;	

	Vector3f direction;

	if (!if_refract || reflectance(cos_theta, ri) > random_float())
		direction = r_in.reflect(rec.normal.normalized());
	else
		direction = r_in.refract(rec.normal.normalized(), ri);

	scattered = Ray(rec.p, direction);
	return true;
}

float Dielectric::reflectance(float cosine, float ri) {
	auto r0 = (1 - ri) / (1 + ri);
	r0 *= r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}