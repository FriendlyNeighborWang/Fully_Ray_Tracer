#include "Camera.h"

void Camera::initialize() {
	image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	float theta = degrees_to_radians(vfov);
	float h = tan(theta / 2);
	auto viewport_height = 2 * h * focus_dist;
	auto viewport_width = viewport_height * (float(image_width) / image_height);

	w = (lookfrom - lookat).normalized();
	u = vup.cross(w).normalized();
	v = w.cross(u);

	auto viewport_u = viewport_width * u;
	auto viewport_v = viewport_height * -v;

	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	auto viewport_upper_left = lookfrom - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
	pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
	defocus_disk_u = defocus_radius * u;
	defocus_disk_v = defocus_radius * v;

	std::clog << "Camera has been initialized!" << std::endl;

}

Ray Camera::get_ray(int i, int j) const {
	auto offset = sample_square();
	auto pixel_sample = pixel_00 + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

	auto ray_origin = (defocus_angle <= 0) ? lookfrom : defocus_disk_sample();
	auto ray_direction = pixel_sample - ray_origin;
	return Ray(ray_origin, ray_direction);
}

inline Vector3f Camera::sample_square() const {
	return Vector3f(random_float(-0.5, 0.5), random_float(-0.5, 0.5), 0);
}

inline Point3f Camera::defocus_disk_sample() const {
	auto p = random_in_unit_disk();
	return lookfrom + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

inline Vector3f Camera::random_in_unit_disk() {
	while (true) {
		auto p = Vector3f(random_float(-1, 1), random_float(-1, 1), 0);
		if (p.norm() < 1)
			return p;
	}
}