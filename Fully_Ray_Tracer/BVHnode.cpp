#include "BVHnode.h"

BVHnode::BVHnode(Container& list, axis a) :obj_list(list), aabb(obj_list[0]->aabb) {
	// Build AABB
	for (auto obj : obj_list)
		aabb.merge(obj->aabb);

	// Sort
	auto mid = obj_list.begin() + obj_list.size() / 2;
	std::nth_element(obj_list.begin(), mid, obj_list.end(),
		[&](std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2)->bool {
			return obj1->aabb.mid()[a] < obj2->aabb.mid()[a];
		});

	if (obj_list.size() < 4) {
		if_leaf = true;
		std::clog << "Acceleration Structure has been built!  Type: BVH + Rotating-axis splitting" << std::endl;
		return;
	}

	auto next_axis = static_cast<axis>((a + 1) % 3);
	left = std::make_shared<BVHnode>(obj_list.begin(), mid, next_axis);
	right = std::make_shared<BVHnode>(mid, obj_list.end(), next_axis);

	obj_list.clear();

	std::clog << "Acceleration Structure has been built!  Type: BVH + Rotating-axis splitting" << std::endl;
}


BVHnode::BVHnode(Container::iterator begin, Container::iterator end, axis a) :obj_list(begin, end), aabb(obj_list[0]->aabb) {
	// Build AABB
	for (auto obj : obj_list)
		aabb.merge(obj->aabb);

	// Sort
	auto mid = obj_list.begin() + obj_list.size() / 2;
	std::nth_element(obj_list.begin(), mid, obj_list.end(),
		[&](std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2)->bool {
			return obj1->aabb.mid()[a] < obj2->aabb.mid()[a];
		});

	if (obj_list.size() < 4) {
		if_leaf = true;
		return;
	}

	auto next_axis = static_cast<axis>((a + 1) % 3);
	left = std::make_shared<BVHnode>(obj_list.begin(), mid, next_axis);
	right = std::make_shared<BVHnode>(mid, obj_list.end(), next_axis);

	obj_list.clear();
}

bool BVHnode::intersect(const Ray& r, Interval bound, Inter_record& rec) const {
	bool hit_anything = false;

	if (!aabb.intersect(r, bound))
		return hit_anything;

	if (!if_leaf) {
		Inter_record left_rec, right_rec;
		bool hit_left = left->intersect(r, bound, left_rec);
		bool hit_right = right->intersect(r, bound, right_rec);

		if (hit_right && hit_left)
			rec = std::move(left_rec.t < right_rec.t ? left_rec : right_rec);
		else if (hit_right)
			rec = std::move(right_rec);
		else if (hit_left)
			rec = std::move(left_rec);

		hit_anything = hit_left || hit_right;
	}
	else {
		Inter_record temp_rec;
		auto closest_so_far = bound.max;
		for (const auto& obj : obj_list) {
			if (obj->intersect(r, Interval(bound.min, closest_so_far), temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
	}
	return hit_anything;
}