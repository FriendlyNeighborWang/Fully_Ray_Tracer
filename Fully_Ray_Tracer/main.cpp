#include "Renderer.h"
#include "Sphere.h"

#ifdef DEBUG
std::mutex buffer_mtx;
#endif // DEBUG


int main() {
	Scene world;

	// World component
	auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3f(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++b) {
			auto choose_mat = random_float();
			Point3f center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

			if ((center - Point3f(4, 0.2, 0)).norm() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8f) {
					// diffuse
					Color albedo = random_vec() * random_vec();
					sphere_material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					Color albedo = random_vec(0.5, 1);
					auto fuzz = random_float(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(Point3f(0, 1, 0), 1.0f, material1));

	auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3f(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3f(4, 1, 0), 1.0, material3));


	world.build_acceleration();

	Camera cam(Point3f(13, 2, 3),
		Point3f(0, 0, 0), 1600, 16.0f / 9.0f, 20.0f, 10.0f, 0.6f);
	cam.initialize();

	Renderer renderer(world, cam);
#ifdef DEBUG
	auto& image = renderer.debug_render(100, 5, Vector2i(0, 0), Vector2i(50, 50));
	image.show("Ray-Tracring (Debug)");
	image.save("Debug_output.jpg");
#else
	auto& image = renderer.render(500, 10);
	image.show();
	image.save();
#endif // DEBUG
	

	cv::waitKey(0);
}