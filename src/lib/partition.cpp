#include <vector>
#include <set>
#include <iostream>

#include "partition.h"

Partition::Partition(long tableSize) {
	setRepresentation_ = Partition::SetRepresentation();
	tableSize_ = tableSize;
}

Partition::~Partition() {
	for (SetRepresentation::iterator it = setRepresentation_.begin(); it != setRepresentation_.end(); ++it) {
		delete *it;
	}
}

long Partition::getGroupCount() const {
	return setRepresentation_.size();
}

Partition::ArrayRepresentation* Partition::getArrayRepresentation() const {
	Partition::ArrayRepresentation* ar = new Partition::ArrayRepresentation(tableSize_);
	long groupId = 0;
	for (SetRepresentation::const_iterator it = setRepresentation_.begin(); it != setRepresentation_.end(); ++it) {
		for (Group::iterator jt = (*it)->begin(); jt != (*it)->end(); ++jt) {
			(*ar)[*jt] = groupId;
		}
		groupId++;
	}
	return ar;
}

void Partition::addGroup(Partition::Group* newGroup) {
	setRepresentation_.push_back(newGroup);
}

Partition::Group* Partition::getGroup(long index) const {
	return setRepresentation_[index];
}

void Partition::print() const {
	std::cout << "{";
	for (SetRepresentation::const_iterator it = setRepresentation_.begin(); it != setRepresentation_.end(); ++it) {
		std::cout << "{";
		for (Group::iterator jt = (*it)->begin(); jt != (*it)->end(); ++jt) {
			std::cout << *jt << ",";
		}
		std::cout << "},";
	}
	std::cout << "}" << std::endl;
}