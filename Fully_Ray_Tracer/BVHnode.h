#pragma once
#include "AABB.h"
#include "Object.h"

class BVHnode {
	using Container = std::vector<std::shared_ptr<Object>>;
	enum axis { X = 0, Y, Z };
public:	
	BVHnode(){}
	BVHnode(Container& list, axis a = X);
	BVHnode(Container::iterator begin, Container::iterator end, axis a);
	bool intersect(const Ray& r, Interval bound, Inter_record& rec) const;

private:
	Container obj_list;
	bool if_leaf = false;
	AABB aabb;
	std::shared_ptr<BVHnode> left;
	std::shared_ptr<BVHnode> right;
};