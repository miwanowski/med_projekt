#include <iostream>
#include <set>
#include <vector>

#include "fun.h"
#include "utils.h"

typedef std::vector<long> ArrayRepresentation;
typedef std::set<long> Group;

int main() {
	{
		// Partition* a = new Partition(10);
		// Group* ng = new Group();
		// ng->insert(0); ng->insert(1); ng->insert(2);
		// a->addGroup(ng);
		// ng = new Group();
		// ng->insert(3); ng->insert(4); ng->insert(5); ng->insert(6); ng->insert(7); ng->insert(8); ng->insert(9); 
		// a->addGroup(ng);
		// a->print();

		// ArrayRepresentation* ar = a->getArrayRepresentation();
		// printArrayRepresentation(ar);
		// delete ar;

		// Partition* b = new Partition(10);
		// ng = new Group();
		// ng->insert(0);
		// b->addGroup(ng);
		// ng = new Group();
		// ng->insert(1); ng->insert(2); ng->insert(3); ng->insert(4); ng->insert(5);
		// b->addGroup(ng);
		// ng = new Group();
		// ng->insert(6); ng->insert(7); ng->insert(8); ng->insert(9);
		// b->addGroup(ng);
		// b->print();

		// ar = b->getArrayRepresentation();
		// printArrayRepresentation(ar);

		// Partition* c = Fun::product(a, b);
		// c->print();
		// CandidateSet* cs = new CandidateSet();
		// std::cout << "cs->getSize() = " << cs->getSize() << std::endl;

		// return 0;

		// CandidateSet* cs = new CandidateSet();
		// Partition* d = new Partition();

		std::vector<int> aids;
		aids.push_back(1); aids.push_back(2); aids.push_back(3); aids.push_back(4); aids.push_back(5);

		Fun::holdsVariant_ = &Fun::partReducedStrippedHolds;
		Fun::productVariant_ = &Fun::strippedProduct;

		CandidateSet res = Fun::fun("tests/przyklad.csv", aids, 6);
		std::cout << "Results:" << std::endl;
		for (int i = 0; i < res.getSize(); ++i) {
			printAttributeList(res[i]->getAttributeList());
			std::cout << std::endl;
		}
	}
}