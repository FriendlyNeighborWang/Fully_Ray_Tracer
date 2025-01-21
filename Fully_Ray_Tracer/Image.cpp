#include "Image.h"

void Image::paint(int x, int y, Color color) {
	auto r = color.x();
	auto g = color.y();
	auto b = color.z();

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	static const Interval intensity(0.000f, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	std::shared_lock<std::shared_mutex> lock(mtx);
	img.at<cv::Vec3b>(y, x) = cv::Vec3b(rbyte, gbyte, bbyte);
}


void Image::refresh() {
	while (keep_refresh) {
		show();
		cv::waitKey(50);
	}
}



