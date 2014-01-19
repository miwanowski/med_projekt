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

		const int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
		std::vector<int> aids(arr, arr + sizeof(arr) / sizeof(arr[0]));

		Fun::holdsVariant_ = &Fun::partReducedStrippedHolds;
		Fun::productVariant_ = &Fun::strippedProduct;

		CandidateSet res = Fun::fun("tests/letter-recognition1000.csv", aids, 0);
		std::cout << "Results:" << std::endl;
		for (int i = 0; i < res.getSize(); ++i) {
			printAttributeList(res[i]->getAttributeList());
			std::cout << std::endl;
		}
	}
}