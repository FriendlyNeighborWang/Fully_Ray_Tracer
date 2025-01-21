#pragma once
#include "Object.h"
#include "BVHnode.h"

class Scene {
public:
	Scene() {}
	Scene(std::shared_ptr<Object> obj) {}

	inline void clear() { obj_list.clear(); }
	inline void add(std::shared_ptr<Object> obj) { obj_list.push_back(obj); }
	inline void build_acceleration() { use_acceleration = true; bvh = BVHnode(obj_list); }
	bool intersect(const Ray& r, Interval bound, Inter_record& rec) const;

private:
	std::vector<std::shared_ptr<Object>> obj_list;
	bool use_acceleration = false;
	BVHnode bvh;
};