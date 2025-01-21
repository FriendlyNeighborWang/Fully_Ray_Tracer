#include "Renderer.h"

Image& Renderer::render(int samples_per_pixel, int depth) {
	this->samples_per_pixel = samples_per_pixel;
	this->pixel_sample_scale = 1.0f / samples_per_pixel;
	this->max_depth = depth;

	thread_pool.start();

	// Refresh
	auto refresh_task = std::bind(&Image::refresh, &img);
	std::thread refresh_thread(refresh_task);

	int col = camera.get_width();
	int row = camera.get_height();
	int task_row = row / 20;
	int task_col = col / 20;
	for (int start_row = 0; start_row < row; start_row += task_row) {
		int end_row = std::min(start_row + task_row, row);
		for (int start_col = 0; start_col < col; start_col += task_col) {
			int end_col = std::min(start_col + task_col, col);

			auto task = std::bind(&Renderer::thread_render_task, this, Vector2i(start_col, start_row), Vector2i(end_col, end_row));
			thread_pool.submit(task);
		}
	}
	thread_pool.wait_and_stop();

	img.stop_refresh();
	refresh_thread.join();

	return img;
}

Image& Renderer::debug_render(int samples_per_pixel, int depth, Vector2i up_left, Vector2i down_right) {
	this->samples_per_pixel = samples_per_pixel;
	this->pixel_sample_scale = 1.0f / samples_per_pixel;
	this->max_depth = depth;

	thread_pool.start();
	
	// Refresh
	auto refresh_task = std::bind(&Image::refresh, &img);
	std::thread refresh_thread(refresh_task);

	auto task = std::bind(&Renderer::thread_render_task, this, up_left, down_right);
	thread_pool.submit(task);
	
	thread_pool.wait_and_stop();

	img.stop_refresh();
	refresh_thread.join();
	
	return img;
}

void Renderer::thread_render_task(Vector2i left_up, Vector2i right_down) {
	auto start_row = left_up.y();
	auto end_row = right_down.y();
	auto begin_col = left_up.x();
	auto end_col = right_down.x();
	for (int y = start_row; y < end_row; ++y) {
		for (int x = begin_col; x < end_col; ++x) {
			Color pixel_color(0, 0, 0);
			for (int sample = 0; sample < samples_per_pixel; ++sample) {
				Ray r = camera.get_ray(x, y);
				pixel_color += ray_color(r, max_depth);
			}
			auto result = pixel_sample_scale * pixel_color;
			img.paint(x, y, pixel_sample_scale * pixel_color);
		}
	}
}

Color Renderer::ray_color(const Ray& r, int depth) {
	if (depth <= 0)
		return Color(0.0f, 0.0f, 0.0f);

	Inter_record rec;

	if (world.intersect(r, Interval(0.001, INF), rec)) {
		Ray scattered;
		Color attenuation;
		if (rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, depth - 1);
		return Color(0.0f, 0.0f, 0.0f);
	}
	Vector3f unit_direction = r.dir().normalized();
	float a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}