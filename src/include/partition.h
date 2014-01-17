/*
* Class representing a partition with respect to a given
* set of attributes (Candidate object). 
*/

#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <set>

class Partition
{
	// temporary, maybe other data structures would be better:
	typedef std::vector<long> ArrayRepresentation;
	typedef std::set<long> Group;

public:
	// construct an empty partition:
	Partition();

	// get the number of groups:
	long getGroupCount() const;

	// get the array representation:
	ArrayRepresentation* getArrayRepresentation() const;

	// add a new group to partition
	void addGroup(Group* newGroup);

	// get a group by index:
	Group* getGroup(long index);
};

#endif