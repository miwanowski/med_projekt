#include <iostream>
#include <set>
#include <vector>

#include "fun.h"

typedef std::vector<long> ArrayRepresentation;
typedef std::set<long> Group;

void printArrayRepresentation(ArrayRepresentation* ar) {
	int i = 0;
	for (ArrayRepresentation::iterator it = ar->begin(); it != ar->end(); ++it) {
		std::cout << i << ": " << *it << ", ";
		i++;
	}
	std::cout << std::endl;
}


int main() {

	{
		Partition* a = new Partition(10);
		Group* ng = new Group();
		ng->insert(0); ng->insert(1); ng->insert(2);
		a->addGroup(ng);
		ng = new Group();
		ng->insert(3); ng->insert(4); ng->insert(5); ng->insert(6); ng->insert(7); ng->insert(8); ng->insert(9); 
		a->addGroup(ng);
		a->print();

		ArrayRepresentation* ar = a->getArrayRepresentation();
		printArrayRepresentation(ar);

		Partition* b = new Partition(10);
		ng = new Group();
		ng->insert(0);
		b->addGroup(ng);
		ng = new Group();
		ng->insert(1); ng->insert(2); ng->insert(3); ng->insert(4); ng->insert(5);
		b->addGroup(ng);
		ng = new Group();
		ng->insert(6); ng->insert(7); ng->insert(8); ng->insert(9);
		b->addGroup(ng);
		b->print();

		ar = b->getArrayRepresentation();
		printArrayRepresentation(ar);

		Partition* c = Fun::product(a, b);
		c->print();
	}
}