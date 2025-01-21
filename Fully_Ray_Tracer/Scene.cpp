#include "Scene.h"

bool Scene::intersect(const Ray& r, Interval bound, Inter_record& rec) const {
	if(use_acceleration)
		return bvh.intersect(r, bound, rec);
	
	Inter_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = bound.max;
	for (const auto& obj : obj_list) {
		if (obj->intersect(r, Interval(bound.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}