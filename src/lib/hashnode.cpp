#include "hashnode.h"

void InternalNode::printNode(int level) {
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

void LeafNode::printNode(int level) {
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

InternalNode::~InternalNode() {
	for (int i=0; i < order_; ++i) {
		if (children_[i] != NULL) {
			delete children_[i];
		}
	}
}