#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <algorithm>
#include <Eigen/Dense>

// Using and Naming
using Eigen::Vector3f;
using Eigen::Vector2i;
using Point3f = Vector3f;

// Constants
constexpr float INF = std::numeric_limits<float>::infinity();
constexpr float EPS = 1e-6;
constexpr double PI = 3.14159265358979;

// Utility Functions
inline float degrees_to_radians(float degrees) {
	return float(degrees * PI / 180.0);
}

inline float random_float(float min = 0.0f, float max = 1.0f) {
	static std::uniform_real_distribution<float> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

inline static Vector3f random_vec(float min = 0.0f, float max = 1.0f) {
	return Vector3f(random_float(min, max), random_float(min, max), random_float(min, max)).normalized();
}


inline Vector3f random_unit_vec() {
	while (true) {
		auto p = random_vec(-1, 1);
		if (p.norm() < 1)
			return p.normalized();
	}
}
