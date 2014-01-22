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

	~HashTree(){ };

	// insert a new candidate into the tree
	void insertCandidate(AttributeList al/*Candidate* newCandidate*/);

	// find how many subsets of a given candidate already exist in a tree
	int findNumberOfPresentSubsets(AttributeList al /*Candidate* c*/);

	// delete a candidate from the tree
	void deleteCandidate(AttributeList al /*Candidate *c*/);

	// for debugging:
	void printTree();
};

#endif