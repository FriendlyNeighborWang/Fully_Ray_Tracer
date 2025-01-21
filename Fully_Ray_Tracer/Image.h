#pragma once
#include "Color.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <shared_mutex>

class Image {
public:
	Image(int height, int width) :img(height, width, CV_8UC3, cv::Scalar(0, 0, 0)){}
	
	inline void show(std::string name = "Ray Tracing") {
		std::unique_lock<std::shared_mutex> lock(mtx);
		cv::imshow(name, img);
	}

	inline void save(std::string path = "output.jpg") {
		std::unique_lock<std::shared_mutex> lock(mtx);
		cv::imwrite(path, img);
	}

	void paint(int x, int y, Color color);

	inline float linear_to_gamma(float linear_component) {
		if (linear_component > 0)
			return sqrt(linear_component);
	}

	inline void start_refresh() { keep_refresh = true; }

	inline void stop_refresh() { keep_refresh = false; }

	void refresh();

private:
	cv::Mat img;
	std::shared_mutex mtx;
	std::atomic_bool keep_refresh = true;
};

