/*
* Class representing a hash tree for storing candidates
* and quick lookup of subsets of a given candidate.
*/

#ifndef HASHTREE_H
#define HASHTREE_H

#include <vector>

#include "hashnode.h"
#include "candidate.h"

class HashTree {
public:
	typedef std::vector<int> CandidateRepresentation;
	typedef Candidate::AttributeList AttributeList;
	typedef LeafNode::CandidateList CandidateList;

private:
	// restricted, not implemented argumentless constructor:
	HashTree();

	// order of the tree:
	int order_;

	// root node:
	HashNode* root_;

public:
	// construct a tree of a given order
	HashTree(int order);

	~HashTree();

	// insert a new candidate into the tree
	void insertCandidate(Candidate* newCandidate, bool includeGroupCount=false);

	// find how many subsets of a given candidate already exist in a tree
	int findNumberOfPresentSubsets(Candidate* c, long groupCount=0) const;

	// check if the tree contains a given candidate:
	bool contains(AttributeList& al, long groupCount=0) const;

		// delete a candidate from the tree
	void deleteCandidate(Candidate *c);

	// for debugging:
	void printTree() const;
};

#endif