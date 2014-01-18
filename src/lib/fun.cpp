#include <cstddef>

#include "fun.h"

Partition* Fun::product(Partition* a, Partition* b) {
	Partition* c = new Partition(a->getTableSize());
	ArrayRepresentation* t = a->getArrayRepresentation();
	std::vector<Group*> s = std::vector<Group*>(a->getTableSize());

	for (long groupId = 0; groupId < b->getGroupCount(); ++groupId) {
		Group* group = b->getGroup(groupId);
		Group aGroupIds;
		for (Group::const_iterator it = group->begin(); it != group->end(); ++it) {
			long j = (*t)[*it];
			if (s[j] == NULL)
				s[j] = new Group();
			s[j]->insert(*it);
			aGroupIds.insert(j);
		}
		for (Group::const_iterator it = aGroupIds.begin(); it != aGroupIds.end(); ++it) {
			c->addGroup(s[*it]);
			s[*it] = NULL;
		}
	}
	delete t;
	return c;
}

bool Fun::holds(Candidate* c, Partition* d) {
	ArrayRepresentation* t = d->getArrayRepresentation();
	Partition* cp = c->getPartition();
	for (long groupId = 0; groupId < cp->getGroupCount(); ++groupId) {
		Group* group = cp->getGroup(groupId);
		Group::const_iterator it = group->begin();
		long firstGroup = (*t)[*it];
		++it;
		for (; it != group->end(); ++it) {
			if (firstGroup != (*t)[*it]) {
				delete t;
				return false;
			}
		}
	}
	delete t;
	return true;
}