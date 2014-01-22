#include <vector>
#include <string>

#include "hashtree.h"
#include "utils.h"

// construct a tree of a given order
HashTree::HashTree(int order) {
	order_ = order;
	root_ = new InternalNode(order_);
}

HashTree::~HashTree() {
	delete root_;
}

// insert a new candidate into the tree
void HashTree::insertCandidate(Candidate* newCandidate) {
	AttributeList al = newCandidate->getAttributeList();
	AttributeList::iterator at = al.begin();
	HashNode* currentNode = root_;
	HashNode* parentNode = NULL;
	int lastHash = -1;
	int depth = 0;
	// find the place in the tree to add the candidate:
	while (!currentNode->isLeaf() && at != al.end()) {
		parentNode = currentNode;
		currentNode = ((InternalNode*)currentNode)->getChild(*at % order_);
		lastHash = *at % order_;
		at++;
		depth++;
		if (currentNode == NULL)
			break;
	}
	if (currentNode == NULL) {
		// arrived at a "hanging" branch, need to create a new leaf node:
		currentNode = new LeafNode();
		((LeafNode*)currentNode)->candidates_.push_back(al);
		((InternalNode*)parentNode)->setChild(lastHash, currentNode);
	} else if (at != al.end()) {
		// arrived at a leaf node and still have elements to hash,
		// need to transform the leaf node into an internal node
		InternalNode* newInternalNode = new InternalNode(order_);
		((InternalNode*)parentNode)->setChild(lastHash, newInternalNode);
		for (CandidateList::iterator it = ((LeafNode*)currentNode)->candidates_.begin();
			it != ((LeafNode*)currentNode)->candidates_.end(); ++it)
		{
			int newHash = (*it)[depth] % order_;
			if (newInternalNode->getChild(newHash) == NULL) {
				newInternalNode->setChild(newHash, new LeafNode());
			}
			((LeafNode*)newInternalNode->getChild(newHash))->candidates_.push_back(*it);
		}
		int newHash = *at % order_;
		if (newInternalNode->getChild(newHash) == NULL) {
			newInternalNode->setChild(newHash, new LeafNode());
		}
		((LeafNode*)newInternalNode->getChild(newHash))->candidates_.push_back(al);
		delete currentNode;
	} else {
		// arrived at a leaf node and there are no more elements to hash,
		// need to append the candidate to the list
		((LeafNode*)currentNode)->candidates_.push_back(al);
	}
}

// delete a candidate from the tree
void HashTree::deleteCandidate(Candidate *c) {
	AttributeList al = c->getAttributeList();
	HashNode* currentNode = root_;
	for (AttributeList::iterator at = al.begin(); at != al.end(); ++at) {
		int newHash = *at % order_;
		currentNode = ((InternalNode*)currentNode)->getChild(newHash);
		if (currentNode->isLeaf())
			break;
	}
	CandidateList::iterator ca = ((LeafNode*)currentNode)->candidates_.begin();
	while (ca != ((LeafNode*)currentNode)->candidates_.end()) {
		if (std::equal(ca->begin(), ca->end(), al.begin())) {
			ca = ((LeafNode*)currentNode)->candidates_.erase(ca);
		} else {
			++ca;
		}
	}
}

// check if the tree contains a given candidate:
bool HashTree::contains(AttributeList& al) const {
	HashNode* currentNode = root_;
	for (AttributeList::iterator at = al.begin(); at != al.end(); ++at) {
		int newHash = *at % order_;
		currentNode = ((InternalNode*)currentNode)->getChild(newHash);
		if (currentNode == NULL)
			return false;
		if (currentNode->isLeaf())
			break;
	}
	for (CandidateList::iterator c = ((LeafNode*)currentNode)->candidates_.begin();
			c != ((LeafNode*)currentNode)->candidates_.end(); ++c) {
		if (std::equal(c->begin(), c->end(), al.begin())) {
			return true;
		}
	}
	return false;
}

// find how many subsets of a given candidate already exist in a tree:
int HashTree::findNumberOfPresentSubsets(Candidate* c) const {
	AttributeList al = c->getAttributeList();
	int count=0;
	for (AttributeList::iterator it = al.begin(); it != al.end(); ++it) {
		AttributeList subset = al;
		int offset = it - al.begin();
		subset.erase(subset.begin() + offset);
		if (contains(subset))
			count++;
	}
	return count;
}

// for debugging:
void HashTree::printTree() const {
	std::cout << std::endl;
	root_->printNode(0);
	std::cout << std::endl;
}