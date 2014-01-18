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