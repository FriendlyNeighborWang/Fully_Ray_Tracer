#pragma once
#include "util.h"
#include "Color.h"
#include "Object.h"

class Material {
public:
	virtual bool scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const = 0;
};

// Diffuse Reflection
class Lambertian : public Material {
public:
	Lambertian(const Color& albedo):albedo(albedo){}
	bool scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
};

class Metal : public Material {
public:
	Metal(const Color& albedo, double fuzz = 0.0) :albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
	bool scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const override ;

private:
	Color albedo;
	float fuzz;
};

class Dielectric :public Material {
public:
	Dielectric(float refraction_index):refraction_index(refraction_index){}
	bool scatter(const Ray& r_in, const Inter_record& rec, Color& attenuation, Ray& scattered) const override;

private:
	float refraction_index;
	static float reflectance(float cosine, float ri);
};