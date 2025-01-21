#pragma once
#include "util.h"
#include "Color.h"
#include "Scene.h"
#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Thread_pool.h"

class Renderer {
public:
	Renderer(const Scene& w, const Camera& cam) : world(w), camera(cam), img(cam.get_height(), cam.get_width()) {}

	Image& render(int samples_per_pixel, int depth);
	Image& debug_render(int samples_per_pixel, int depth, Vector2i up_left, Vector2i down_right);
private:
	void thread_render_task(Vector2i left_up, Vector2i right_down);

	Color ray_color(const Ray& r, int depth) ;

	const Scene& world;
	const Camera& camera;
	Image img;
	Thread_pool thread_pool;
	int samples_per_pixel = 1;
	float pixel_sample_scale = 1.0f;
	int max_depth = 1;
};