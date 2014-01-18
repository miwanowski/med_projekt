/*
* Class representing a single candidate (a set of attributes). 
* Should allow accessing individual attributes and contain a 
* pointer to associated Partition object.
*/

#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <vector>
#include "partition.h"

class Candidate
{
	// temporary, maybe attributeType should be something different:
	typedef char attributeType;
	typedef std::vector<attributeType> AttributeList;

private:
	// pointer to associated partition object:
	Partition* partition_;
	AttributeList* attributeList_;

public:
	// construct a candidate with a given partition:
	Candidate(Partition* newPartition);

	// accessors for partition_:
	Partition* getPartition() const { return partition_; }
	void setPartition(Partition* newPartition) { partition_ = newPartition; }

	// accessors for attributeList_:
	AttributeList* getAttributeList() const { return attributeList_; }  
	void setAttributeList(AttributeList* newAttributeList) { attributeList_ = newAttributeList; }
};

#endif