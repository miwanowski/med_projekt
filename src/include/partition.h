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
public:
	// temporary, maybe other data structures would be better:
	typedef std::set<long> Group;
	typedef std::vector<long> ArrayRepresentation;
	typedef std::vector<Group*> SetRepresentation;

private:
	// internal representation based on sets:
	SetRepresentation setRepresentation_;
	long tableSize_;
	long singletonGroups_;

public:
	// construct an empty partition:
	Partition();
	Partition(long tableSize);

	// delete all groups:
	~Partition();

	// get the number of groups:
	long getGroupCount() const;

	// accessors for tableSize_:
	long getTableSize() const { return tableSize_; }
	void setTableSize(long tableSize) { tableSize_ = tableSize; }

	// accessors for singletonGroups_:
	long getSingletonGroups() const { return singletonGroups_; }
	void setSingletonGroups(long singletonGroups) { singletonGroups_ = singletonGroups; }

	// get the array representation:
	ArrayRepresentation* getArrayRepresentation() const;

	// add a new group to partition:
	void addGroup(Group* newGroup);

	// get a group by index:
	Group* getGroup(long index) const;

	// delete a group by index:
	void deleteGroup(long index);

	// print to stdout for debugging:
	void print() const;
};

#endif