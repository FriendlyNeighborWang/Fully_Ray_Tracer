#pragma once
#include "util.h"
#include "Ray.h"

class Camera {
public:
	Camera(Point3f lookfrom = Point3f(0, 0, 0),
		Point3f lookat = Point3f(0, 0, -1),
		int image_width = 100,
		float aspect_ratio = 1.0,
		float vfov = 90,
		float focus_dist = 10,
		float defocus_angle = 0
	) :lookfrom(lookfrom), lookat(lookat), image_width(image_width), aspect_ratio(aspect_ratio), vfov(vfov),focus_dist(focus_dist),defocus_angle(defocus_angle) {}

	void initialize();
	void set_aspect_ratio(const float& ar) { aspect_ratio = ar; image_height = int(image_width / aspect_ratio); }
	void set_image_width(const int& w) { image_width = w; image_height = int(image_width / aspect_ratio); }
	void set_vfov(const int& v) { vfov = v; }
	void set_defocus_angle(const float& a) { defocus_angle = a; }
	void set_focus_dist(const float& d) { focus_dist = d; }
	void set_lookfrom(const Point3f& o) { lookfrom = o; }
	void set_lookat(const Point3f& d) { lookat = d; }

	int get_width() const { return image_width; }
	int get_height() const { return image_height; }

	Ray get_ray(int i, int j) const;

private:
	inline Vector3f sample_square() const;
	inline Point3f defocus_disk_sample() const;
	inline static Vector3f random_in_unit_disk();

	float aspect_ratio ;
	int image_width;
	int image_height;
	float vfov;
	float defocus_angle;  // Depth of field
	float focus_dist;

	Point3f lookfrom;
	Vector3f lookat;
	Vector3f vup = Vector3f(0, 1, 0);
	
	Vector3f u, v, w;
	Point3f pixel_00;
	Vector3f pixel_delta_u;
	Vector3f pixel_delta_v;
	Vector3f defocus_disk_u;
	Vector3f defocus_disk_v;
};