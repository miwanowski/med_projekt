#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "utils.h"
#include "fun.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void printArrayRepresentation(std::vector<long>* ar) {
	int i = 0;
	for (std::vector<long>::iterator it = ar->begin(); it != ar->end(); ++it) {
		std::cout << i << ": " << *it << ", ";
		i++;
	}
	std::cout << std::endl;
}

void printAttributeList(std::vector<int> al) {
	for (std::vector<int>::iterator it = al.begin(); it != al.end(); ++it) {
		std::cout << Fun::attributeMap[*it] << "(" << *it << ")" << " ";
	}
}

bool isSubset(std::vector<int> A, std::vector<int> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}