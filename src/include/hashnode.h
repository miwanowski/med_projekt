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

	// type identification:
	bool isLeaf() { return false; };

	// children pointers accessors:
	HashNode* getChild(int number) { return children_[number]; };
	bool setChild(int number, HashNode* child) { children_[number] = child; }

	void printNode(int level) {
		for (int i=0; i < level; ++i) {
			std::cout << "-";
		}
		std::cout << " internal node: [";
		for (int i=0; i < order_; ++i) {
			if (children_[i] == NULL)
				std::cout << "n,";
			else if (children_[i]->isLeaf())
				std::cout << "l,";
			else 
				std::cout << "i,";
		}
		std::cout << "]" << std::endl;
		for (int i=0; i < order_; ++i) {
			if (children_[i] != NULL)
				children_[i]->printNode(level+1);
		}
	}
};

class LeafNode : public HashNode {
public:
	// list type for storing candidates:
	typedef std::vector<std::vector<int> > CandidateList;

	// empty constructor:
	LeafNode() { };

	// type identification:
	bool isLeaf() { return true; };	

	void printNode(int level) {
		for (int i=0; i < level; ++i) {
			std::cout << "-";
		}
		std::cout << " leaf node with candidates:" << std::endl;
		for (int j=0; j < candidates_.size(); ++j) {
			for (int i=0; i < level; ++i) {
				std::cout << "-";
			}
			std::cout << " ";
			for (int k=0; k < candidates_[j].size(); ++k) {
				std::cout << candidates_[j][k] << " ";
			}
			std::cout << std::endl;
		}
		
	}

	// public member with the list of candidates:
	CandidateList candidates_;
};

#endif