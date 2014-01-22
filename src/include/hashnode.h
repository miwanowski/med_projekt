/*
* A group of classes for hash tree node representation.
*/

#ifndef HASHNODE_H
#define HASHNODE_H

#include <vector>
#include <iostream>

// abstract class for a hash tree node:
class HashNode {
public:
	// for node type identification
	virtual bool isLeaf() = 0;
	virtual void printNode(int level) = 0;
};

// node with the hash table of pointers:
class InternalNode : public HashNode {
public:
	// type for storing pointers to children nodes:
	typedef std::vector<HashNode*> Children;
private:
	// order of the hashing tree:
	int order_;

	// pointers to children:
	Children children_;
public:
	// constructor initializing order_ field and children table with NULLs:
	InternalNode(int order) : order_(order), children_(order, (HashNode*)0 ) { };

	// destructor that deletes children first:
	~InternalNode();

	// type identification:
	bool isLeaf() { return false; };

	// children pointers accessors:
	HashNode* getChild(int number) { return children_[number]; };
	bool setChild(int number, HashNode* child) { children_[number] = child; }

	// text representation:
	void printNode(int level);

};

class LeafNode : public HashNode {
public:
	// list type for storing candidates:
	typedef std::vector<std::vector<int> > CandidateList;

	// empty constructor:
	LeafNode() { };

	// type identification:
	bool isLeaf() { return true; };	

	// text representation:
	void printNode(int level) ;

	// public member with the list of candidates:
	CandidateList candidates_;
};

#endif